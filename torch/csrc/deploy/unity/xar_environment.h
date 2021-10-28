#pragma once

#include <torch/csrc/deploy/deploy.h>
#include <torch/csrc/deploy/environment.h>
#include <string>

namespace torch {
namespace deploy {

constexpr const char* DEFAULT_PYTHON_APP_DIR = "/tmp/torch_deploy_python_app";

class XarEnvironment : public Environment {
 public:
  explicit XarEnvironment(std::string pythonAppDir = DEFAULT_PYTHON_APP_DIR);
  void setup() override;
  void teardown() override;
  void configureInterpreter(Interpreter* interp) override;

 private:
  void setupPythonApp();
  void preloadSharedLibraries();

  std::string pythonAppDir_;
  std::string pythonAppRoot_;
  bool alreadySetupPythonApp_ = false;
};

} // namespace deploy
} // namespace torch
