#include "generated.h"
#include <string>

using rust::Impl;
using rust::Inventory;
using rust::Item;
using rust::Ref;
using rust::RefMut;
using rust::Str;
using rust::Unit;
using rust::std::ffi::CStr;
using rust::std::fmt::Debug;
using rust::std::fmt::Formatter;
using rust::std::fmt::Result;

Ref<Str> rust_str_from_c_str(const char* input) {
  return CStr::from_ptr(reinterpret_cast<const int8_t*>(input)).to_str().expect("invalid_utf8"_rs);
}

Inventory Impl<Inventory>::new_empty(uint32_t space) {
  return Inventory::build(space);
}

Unit Impl<Inventory>::add_banana(RefMut<Inventory> self, uint32_t count) {
  self.cpp().add_banana(count);
  return {};
}

Unit Impl<Inventory>::add_item(RefMut<Inventory> self, Item item) {
  self.cpp().add_item(item.cpp());
  return {};
}

Item Impl<Item>::new_(Ref<Str> name, uint32_t size) {
  return Item::build(cpp_inventory::Item{
      .name = ::std::string(reinterpret_cast<const char *>(name.as_ptr()),
                            name.len()),
      .size = size});
}

Result Impl<Inventory, Debug>::fmt(Ref<Inventory> self, RefMut<Formatter> f) {
  ::std::string result = "Inventory { remaining_space: ";
  result += ::std::to_string(self.cpp().remaining_space);
  result += ", items: [";
  bool is_first = true;
  for (const auto &item : self.cpp().items) {
    if (!is_first) {
      result += ", ";
    } else {
      is_first = false;
    }
    result += "Item { name: \"";
    result += item.name;
    result += "\", size: ";
    result += ::std::to_string(item.size);
    result += " }";
  }
  result += "] }";
  return f.write_str(rust_str_from_c_str(result.c_str()));
}
