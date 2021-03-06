/* Copyright (c) 2015-2016 The Khronos Group Inc.
 * Copyright (c) 2015-2016 Valve Corporation
 * Copyright (c) 2015-2016 LunarG, Inc.
 * Copyright (C) 2015-2016 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Tobin Ehlis <tobine@google.com>
 * Author: Mark Lobodzinski <mark@lunarg.com>
 */

#include "vulkan/vulkan.h"

#include "vk_layer_data.h"
#include "vk_safe_struct.h"
#include "vk_layer_utils.h"
#include "mutex"

#pragma once

namespace unique_objects {

// All increments must be guarded by global_lock
static uint64_t global_unique_id = 1;

struct TEMPLATE_STATE {
    VkDescriptorUpdateTemplateKHR desc_update_template;
    safe_VkDescriptorUpdateTemplateCreateInfoKHR create_info;

    TEMPLATE_STATE(VkDescriptorUpdateTemplateKHR update_template, safe_VkDescriptorUpdateTemplateCreateInfoKHR *pCreateInfo)
        : desc_update_template(update_template), create_info(*pCreateInfo) {}
};

struct layer_data {
    VkInstance instance;

    debug_report_data *report_data;
    std::vector<VkDebugReportCallbackEXT> logging_callback;
    VkLayerDispatchTable *device_dispatch_table;
    VkLayerInstanceDispatchTable *instance_dispatch_table;

    // The following are for keeping track of the temporary callbacks that can
    // be used in vkCreateInstance and vkDestroyInstance:
    uint32_t num_tmp_callbacks;
    VkDebugReportCallbackCreateInfoEXT *tmp_dbg_create_infos;
    VkDebugReportCallbackEXT *tmp_callbacks;

    std::unordered_map<uint64_t, std::unique_ptr<TEMPLATE_STATE>> desc_template_map;

    bool wsi_enabled;
    std::unordered_map<uint64_t, uint64_t> unique_id_mapping;  // Map uniqueID to actual object handle
    VkPhysicalDevice gpu;

    layer_data() : wsi_enabled(false), gpu(VK_NULL_HANDLE){};
};

struct instance_extension_enables {
    bool wsi_enabled;
    bool xlib_enabled;
    bool xcb_enabled;
    bool wayland_enabled;
    bool mir_enabled;
    bool android_enabled;
    bool win32_enabled;
    bool display_enabled;
};

static std::unordered_map<void *, struct instance_extension_enables> instance_ext_map;
static std::unordered_map<void *, layer_data *> layer_data_map;

static std::mutex global_lock;  // Protect map accesses and unique_id increments

struct GenericHeader {
    VkStructureType sType;
    void *pNext;
};

template <typename T>
bool ContainsExtStruct(const T *target, VkStructureType ext_type) {
    assert(target != nullptr);

    const GenericHeader *ext_struct = reinterpret_cast<const GenericHeader *>(target->pNext);

    while (ext_struct != nullptr) {
        if (ext_struct->sType == ext_type) {
            return true;
        }

        ext_struct = reinterpret_cast<const GenericHeader *>(ext_struct->pNext);
    }

    return false;
}

}  // namespace unique_objects
