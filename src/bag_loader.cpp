#include <digital_twin/bag_loader.hpp>
#include <digital_twin/timestamp.hpp>

#include <rosbag/bag.h>
#include <rosbag/view.h>

#include <vector>
#include <algorithm>
#include <regex>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

namespace digital_twin {

  /******************************************
   * BagDescription 
   */

  BagDescription::BagDescription(const std::string& filename) {
    rosbag::Bag bag;
    bag.open(filename, rosbag::bagmode::Read);

    rosbag::View view(bag);

    // Initialize the topic list
    for (const auto& info : view.getConnections()) {
      if (std::find_if(topics.begin(), topics.end(), [&](auto t) {
							return t.name == info->topic;
						     }) == topics.end()) {
	topics.emplace_back(info->topic, info->datatype);
      }
    }

    // Initialize the series number    
    std::regex series_regex{R"(.+_(\d+).bag)"};
    std::cmatch match;
    if (std::regex_search(filename.c_str(), match, series_regex)) {
      this->series_number = std::stoi(match[1].str());
    }

    // Initialize the start_time
    auto start_time_ros = view.getBeginTime();
    this->start_time = Timestamp{start_time_ros.sec, start_time_ros.nsec};

    // Initialize the end_time
    auto end_time_ros = view.getEndTime();
    this->end_time = Timestamp{end_time_ros.sec, end_time_ros.nsec};

  }

  /******************************************
   * ROSBagLoader
   */
  
  ROSBagLoader::ROSBagLoader(const std::string& path, const std::optional<std::string> pattern) 
    : path_string_{path}
    , file_pattern_{pattern} {

    bag_files_ = fs::path{path_string_};

    std::string path_regex_str;
    
    if (pattern.has_value()) {
      path_regex_str = pattern.value() + R"(_\d*)" + R"(.bag)";
    } else {
      path_regex_str = R"(.bag)";
    }

    std::regex bag_regex{path_regex_str,
			 std::regex_constants::ECMAScript | std::regex_constants::icase};

    // We have a single file.
    if (std::regex_search(bag_files_.string(), bag_regex)) {
      bag_file_names.push_back(bag_files_.string());
    } else {
      // Otherwise we're in a directory, so we iterate.
      for (const auto& dir_entry : fs::directory_iterator{bag_files_}) {
	if (std::regex_search(dir_entry.path().string(), bag_regex)) {
	  if (std::find(bag_file_names.begin(), bag_file_names.end(),
			dir_entry.path().string()) == bag_file_names.end()) {
	    bag_file_names.push_back(dir_entry.path().string());
	  }
	}
      }    
    }

    std::cerr << "There are " << bag_file_names.size() << " bag files." << std::endl;

    // Create bag descriptions
    for (const auto& bag_file_name : bag_file_names) {
      bag_descriptions.emplace_back(std::make_unique<BagDescription>(bag_file_name));
    }

    std::cerr << "There are " << bag_descriptions.size() << " bag descriptions." << std::endl;
    
  }

} // namespace digital_twin
