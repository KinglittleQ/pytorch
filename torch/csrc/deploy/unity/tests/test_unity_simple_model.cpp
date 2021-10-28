#include <fmt/format.h>
#include <gtest/gtest.h>
#include <torch/csrc/deploy/unity/tests/test_unity.h>
#include <torch/csrc/deploy/unity/xar_environment.h>

namespace torch {
namespace deploy {

TEST(UnityTest, TestUnitySimpleModel) {
  // use a different path for unit test. Normally don't specify the path will
  // use the default one.
  std::unique_ptr<Environment> env =
      std::make_unique<XarEnvironment>(TEST_PYTHON_APP_DIR);
  InterpreterManager m(2, std::move(env));

  auto I = m.acquireOne();

  auto noArgs = at::ArrayRef<Obj>();
  auto input = I.global("torch", "randn")({32, 256});
  auto model = I.global("simple_model", "SimpleModel")(noArgs);

  auto output = model({input}); // implicitly calls model's forward method
  EXPECT_EQ(2, output.attr("shape").attr("__len__")(noArgs).toIValue().toInt());
  EXPECT_EQ(
      32, output.attr("shape").attr("__getitem__")({0}).toIValue().toInt());
  EXPECT_EQ(
      10, output.attr("shape").attr("__getitem__")({1}).toIValue().toInt());
}

} // namespace deploy
} // namespace torch
