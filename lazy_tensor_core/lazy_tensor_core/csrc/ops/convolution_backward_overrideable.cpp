#include "lazy_tensor_core/csrc/ops/convolution_backward_overrideable.h"

#include "lazy_tensor_core/csrc/compiler/node_lowering.h"

namespace torch_lazy_tensors {
namespace ir {
namespace ops {

ConvolutionBackwardOverrideable::ConvolutionBackwardOverrideable(
    const torch::lazy::Value& grad_output, const torch::lazy::Value& input,
    const torch::lazy::Value& weight, std::vector<int64_t> stride,
    std::vector<int64_t> padding, std::vector<int64_t> dilation,
    bool transposed, std::vector<int64_t> output_padding, int64_t groups)
    : TsNode(torch::lazy::OpKind(at::aten::convolution_backward_overrideable),
             {grad_output, input, weight},
             /*num_outputs=*/3,
             torch::lazy::MHash(stride, padding, dilation, transposed,
                                output_padding, groups)),
      stride_(std::move(stride)),
      padding_(std::move(padding)),
      dilation_(std::move(dilation)),
      output_padding_(std::move(output_padding)),
      transposed_(transposed),
      groups_(groups) {
  SetShapeDeferred(
      [&]() { return compiler::NodeLowering::Get()->Infer(this); });
}

ConvolutionBackwardOverrideable::ConvolutionBackwardOverrideable(
    const torch::lazy::Value& grad_output, const torch::lazy::Value& input,
    const torch::lazy::Value& weight, std::vector<int64_t> stride,
    std::vector<int64_t> padding, std::vector<int64_t> dilation,
    bool transposed, std::vector<int64_t> output_padding, int64_t groups,
    std::array<bool, 3> output_mask)
    : ConvolutionBackwardOverrideable(grad_output, input, weight, stride,
                                      padding, dilation, transposed,
                                      output_padding, groups) {
  output_mask_ = std::move(output_mask);
}

NodePtr ConvolutionBackwardOverrideable::Clone(OpList operands) const {
  return torch::lazy::MakeNode<ConvolutionBackwardOverrideable>(
      operands.at(0), operands.at(1), operands.at(2), stride_, padding_,
      dilation_, transposed_, output_padding_, groups_);
}

std::string ConvolutionBackwardOverrideable::ToString() const {
  std::stringstream ss;
  ss << TsNode::ToString() << ", stride=(" << c10::Join(", ", stride_)
     << "), padding=(" << c10::Join(", ", padding_) << "), dilation=("
     << c10::Join(", ", dilation_) << "), transpose=" << transposed_
     << ", output_padding=(" << c10::Join(", ", output_padding_)
     << "), groups=" << groups_;
  return ss.str();
}

}  // namespace ops
}  // namespace ir
}  // namespace torch_lazy_tensors
