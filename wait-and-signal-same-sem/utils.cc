// Copyright 2020 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "utils.h"

#include "vulkan_context.h"

VKAPI_ATTR VkBool32 VKAPI_CALL DebugUtilsTestCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT msg_severity, VkDebugUtilsMessageTypeFlagsEXT msg_types,
    const VkDebugUtilsMessengerCallbackDataEXT *callback_data, void *user_data) {
  auto context_with_data = reinterpret_cast<VulkanContext::ContextWithUserData *>(user_data);
  if (msg_severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
    fprintf(stderr, "%s\n", callback_data->pMessage);
    EXPECT_TRUE(context_with_data->context()->validation_errors_ignored());
  } else {
    fprintf(stdout, "%s\n", callback_data->pMessage);
  }
  return VK_FALSE;
}
