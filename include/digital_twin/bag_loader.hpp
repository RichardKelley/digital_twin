#ifndef BAG_LOADER_HPP
#define BAG_LOADER_HPP

#include <fmt/core.h>

#include <digital_twin/timestamp.hpp>
#include <digital_twin/geodetic_point.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <optional>

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

namespace digital_twin {

  struct ROSTopicDescription {
    std::string name;
    std::string type;

    ROSTopicDescription(const std::string n, const std::string t)
      : name{n}, type{t} { }

    std::string to_string() const {
      return fmt::format("ROSTopic({} : {})", name, type);
    }
  };
  
  /*
   * Basic information describing a bag file.
   */
  class BagDescription {
  public:
    std::string filename;

    /*
     * Create a BagDescription from the bagfile with the given
     * filename.
     */
    BagDescription(const std::string& filename);
    
    /*
     * If this bag is one of several in a directory that are part of a
     * collection, the series_number records the integer index at the
     * end of the file name.
     */
    int series_number;

    /*
     * The start and end time are taken from the ROS timestamps of the
     * first and last messages in the bagfile.
     */
    Timestamp start_time;
    Timestamp end_time;

    // A listing of the topics in the bag file.
    std::vector<ROSTopicDescription> topics;
    
    std::vector<std::string> get_topic_for(const std::string& message_type) const {
      std::vector<std::string> ret;
      for (const auto& topic : topics) {
	if (topic.type == message_type) {
	  ret.push_back(topic.name);
	}
      }
      return ret;
    }
    
  };
  
  /*
   * Loader for one or more bag files.
   */
  class ROSBagLoader {
  public:

    ROSBagLoader(const std::string& path,
		 const std::optional<std::string> pattern = std::nullopt);

    inline int get_bagfile_count() const {
      return bag_file_names.size();
    }

    inline std::string get_path_string() const {
      return path_string_;
    }

    std::vector<std::string> bag_file_names;
    std::vector<std::unique_ptr<BagDescription>> bag_descriptions;
    
  private:

    std::string path_string_;
    std::optional<std::string> file_pattern_;
    fs::path bag_files_;
    
  };

} // namespace digital_twin

#endif // BAG_LOADER_HPP
