#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

namespace digital_twin {

  struct Timestamp {
    unsigned int sec;
    unsigned int nsec;

    Timestamp() = default;

    Timestamp(unsigned int s, unsigned int ns)
      : sec{s}, nsec{ns} { }
    
    double to_seconds() const {
      return (double)sec + (double)nsec / 1e-9;
    }
    
  };

} // namespace digital_twin


#endif // TIMESTAMP_HPP
