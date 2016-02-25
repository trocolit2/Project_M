/*
 * GenericRansac.hpp
 *
 *  Created on: Feb 25, 2016
 *      Author: tiagotrocoli
 */

#ifndef SRC_GENERICRANSAC_H_
#define SRC_GENERICRANSAC_H_

#include <vector>
#include <string>
#include <map>

namespace generic_ransac {

template<typename type_data, typename type_return>
class GenericRansac {
 public:
  virtual ~GenericRansac()=0;

  std::vector<type_return> apply(unsigned int iterations, double error_limit,
                                 std::vector<type_data> &input);

  virtual std::string methodName()=0;

 protected:
  virtual double calcError(std::vector<type_data> data)=0;
  virtual unsigned int numberOfSamples()=0;

};

template<typename type_data, typename type_return>
inline std::vector<type_return> GenericRansac<type_data, type_return>::apply(
    unsigned int iterations, double error_limit,
    std::vector<type_data> &input) {

  std::vector<type_return> final_data;
  std::vector<type_data> final_samples;
  std::map<int, type_data> samples;

  for (int i = 0; i < iterations; ++i) {
    while (samples.size() != numberOfSamples()) {
      //random selected
    }

  }
  input = final_samples;
  return final_data;
}

}  // namespace generic_ransac

#endif /* SRC_GENERICRANSAC_H_ */
