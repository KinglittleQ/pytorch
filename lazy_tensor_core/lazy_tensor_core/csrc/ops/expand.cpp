#include "lazy_tensor_core/csrc/ops/expand.h"

#include "lazy_tensor_core/csrc/compiler/node_lowering.h"
#include "lazy_tensors/computation_client/util.h"

namespace torch_lazy_tensors {
namespace ir {
namespace ops {

Expand::Expand(const torch::lazy::Value& input, std::vector<int64_t> size,
               bool is_scalar_expand)
    : TsNode(torch::lazy::OpKind(at::aten::expand), {input},
             /*num_outputs=*/1, torch::lazy::MHash(size, is_scalar_expand)),
      size_(std::move(size)),
      is_scalar_expand_(is_scalar_expand) {
  SetShapeDeferred(
      [&]() { return compiler::NodeLowering::Get()->Infer(this); });
}

NodePtr Expand::Clone(OpList operands) const {
  return torch::lazy::MakeNode<Expand>(operands.at(0), size_, is_scalar_expand_);
}

std::string Expand::ToString() const {
  std::stringstream ss;
  ss << TsNode::ToString() << ", size=(" << c10::Join(", ", size_)
     << "), is_scalar_expand=" << is_scalar_expand_;
  return ss.str();
}

}  // namespace ops
}  // namespace ir
}  // namespace torch_lazy_tensors
