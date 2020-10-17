#include <iostream>
#include <chrono>
#include <utility>
#include <cmath>

#include "../include/interfaces/HCUBE_interface.h"

#include "../include/Hypercube/Hypercube.hpp"
#include "../include/BruteForce/BruteForce.hpp"


int main(int argc, char const *argv[]) {

  /* define the variables */
  interface::ExitCode status;
  interface::Dataset data;
  interface::Dataset queries;
  interface::IOFiles files;
  interface::input::HCUBE::HCUBE_input hc_input;
  // interface::input::HCUBE::HCUBE_input hcube_input;

  /* parse LSH input */
  int ret = interface::input::HCUBE::HCUBEParseInput(argc, argv, hc_input, files, status);

  /* parse dataset */
  int ret3 = interface::ParseDataset(files.input_file, data);

  // std::cout << hc_input.k << '\n';
  // LSH lshmain = LSH(data.number_of_images, 16, 28*28, lsh_input.k, lsh_input.L, lsh_input.R, pow(2,32)-5, data.images);
  Hypercube hcmain = Hypercube(data.number_of_images, 4, 28*28, hc_input.R, pow(2,32)-5, data.images);

  /* parse query set */
  int ret4 = interface::ParseDataset(files.query_file, queries);

  for (int i = 0; i < 5; i++) {
    std::vector<std::pair<int, uint8_t*>> kNNRes = hcmain.ApproxNN(queries.images[i], hc_input.N, hc_input.probes, hc_input.M);

    std::cout << "----" << i << "----" << '\n';
    for (int j = 0; j < kNNRes.size(); j++) {
      std::cout << j << "th Distance - ApproxNN " << kNNRes[j].first << '\n';
    }

    std::vector<std::pair<int, uint8_t*>> rsRes = hcmain.RangeSearch(queries.images[i], hc_input.R, hc_input.probes, hc_input.M);

    std::cout << "----" << i << "----" << '\n';
    for (int j = 0; j < rsRes.size(); j++) {
      std::cout << j << "th Distance - RangeSearch" << rsRes[j].first << '\n';
    }

  }

  return 0;
}
