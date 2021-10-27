#include "lazy_tensors/permutation_util.h"

#include <algorithm>
#include <numeric>

namespace lazy_tensors {

std::vector<int64_t> InversePermutation(
    c10::ArrayRef<int64_t> input_permutation) {
  DCHECK(IsPermutation(input_permutation));
  std::vector<int64_t> output_permutation(input_permutation.size(), -1);
  for (size_t i = 0; i < input_permutation.size(); ++i) {
    output_permutation.at(input_permutation.at(i)) = i;
  }
  return output_permutation;
}

bool IsPermutation(c10::ArrayRef<int64_t> permutation) {
  std::vector<int64_t> trivial_permutation(permutation.size());
  std::iota(trivial_permutation.begin(), trivial_permutation.end(), 0);
  return std::is_permutation(permutation.begin(), permutation.end(),
                             trivial_permutation.begin());
}

bool IsIdentityPermutation(c10::ArrayRef<int64_t> permutation) {
  for (int64_t i = 0; i < permutation.size(); ++i) {
    if (permutation[i] != i) {
      return false;
    }
  }
  return true;
}

}  // namespace lazy_tensors
