/*
 * PointCloud Lib component.
 *
 * Copyright (c) 2018 PointCloud.ai Inc.
 */

#ifndef POINTCLOUD_SERIALIZED_OBJECT_H
#define POINTCLOUD_SERIALIZED_OBJECT_H

#include "Common.h"

#include <string.h>

#include <algorithm>

namespace PointCloud
{
  
class POINTCLOUD_EXPORT SerializedObject
{
protected:
  Vector<char> _bytes;
  uint _getOffset, _putOffset;
  
public:
  SerializedObject(size_t size): _bytes(size), _getOffset(0), _putOffset(0) {}
  SerializedObject(): _getOffset(0), _putOffset(0) {}
  
  uint currentGetOffset() const { return _getOffset; }
  uint currentPutOffset() const { return _putOffset; }
  
  const Vector<char> &getBytes() const { return _bytes; }
  Vector<char> &getBytes() { return _bytes; }
  
  inline void resize(size_t size) 
  { 
    if(size > 0) 
      _bytes.resize(size); 
    else 
      _bytes.clear(); 
    rewind();
  }
  
  inline size_t size() const { return _bytes.size(); }
  
  inline void rewind() { _getOffset = 0; _putOffset = 0; }
  
  inline size_t get(char *bytes, size_t size);
  inline size_t put(const char *bytes, size_t size);
  
  virtual ~SerializedObject() {}
};

size_t SerializedObject::get(char *bytes, size_t size)
{
  //size = std::min(size, _bytes.size() - _getOffset);
  size = size > _bytes.size() - _getOffset ? _bytes.size() - _getOffset : size;
  if(size == 0)
    return 0;
  
  memcpy(bytes, _bytes.data() + _getOffset, size);
  
  _getOffset += size;
  
  return size;
}

size_t SerializedObject::put(const char *bytes, size_t size)
{
  //size = std::min(size, _bytes.size() - _putOffset);

  size = size > _bytes.size() - _putOffset ? _bytes.size() - _putOffset : size;
  if(size == 0)
    return 0;
  
  memcpy(_bytes.data() + _putOffset, bytes, size);
  
  _putOffset += size;
  
  return size;
}
  
  
}


#endif
