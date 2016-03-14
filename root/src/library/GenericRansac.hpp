/*
 * GenericRansac.hpp
 *
 *  Created on: Feb 25, 2016
 *      Author: tiagotrocoli
 */

#ifndef SRC_GENERICRANSAC_H_
#define SRC_GENERICRANSAC_H_

// C libraries
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* clock */

#include <vector>
#include <string>
#include <map>

namespace generic_ransac {

template<typename type_sample, typename type_return>
class GenericRansac {
 public:
  virtual ~GenericRansac()=0;

  std::vector<type_return> apply(unsigned int iterations, double error_limit,
                                 std::vector<type_sample> &input);
  virtual std::string methodName()=0;

 protected:
  virtual std::vector<type_return> applyMethodModel(
      std::vector<type_sample> data)=0;
  virtual double calcError(std::vector<type_return> model, type_sample sample)=0;
  virtual unsigned int numberOfSamples()=0;

 private:
  std::vector<type_sample> mapToVector(std::map<int, type_sample> samples);
};

template<typename type_sample, typename type_return>
inline std::vector<type_return> GenericRansac<type_sample, type_return>::apply(
    unsigned int iterations, double error_limit,
    std::vector<type_sample> &input) {

  std::vector<type_return> final_return, temp_return;
  std::vector<type_sample> final_samples, temp_samples;
  std::map<int, type_sample> map_samples;

  // run main process iteration times
  for (int i = 0; i < iterations; ++i) {
    map_samples.clear();

    while (map_samples.size() != numberOfSamples()) {// samples randomly selected
      srand(clock());  // random based on cpu clock to less replication samples
      int randon_index = rand() % input.size();  // limited random number based on input size
      std::pair<int, type_sample> sample(randon_index, input[randon_index]);
      map_samples.insert(sample); // map structure prevents data duplicity
    }

    temp_samples = mapToVector(map_samples);
    temp_return = applyMethodModel(temp_samples); // caculate method model

    for (int k = 0; k < input.size(); ++k) { // determina o erro de amostra para o modelo atual

    }

  }

  input = final_samples;
  return final_return;
}

}  // namespace generic_ransac

#endif /* SRC_GENERICRANSAC_H_ */
