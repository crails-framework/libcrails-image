#include "image.hpp"
#include <Magick++.h>
#include <sstream>
#include <iostream>

using namespace Crails;
using namespace std;

pair<size_t, size_t> BasicImage::size() const
{
  Magick::Image image(get_filepath());

  return {image.columns(), image.rows()};
}

BasicImage BasicImage::resized(unsigned int width, unsigned int height, int options)
{
  Magick::Image    image(get_filepath());
  Magick::Geometry size(width, height);
  BasicImage       copy(*this);
  stringstream     new_name;

  copy.new_uid();
  size.aspect(options & PreserveAspectRatio);
  image.quality(get_default_image_quality());
  image.resize(size);
  image.magick(extension);
  image.write(copy.get_filepath());
  return copy;
}

static void get_geometry_for_crop_preserving_aspect_ratio(unsigned int width, unsigned int height, unsigned int& max_x, unsigned int& max_y)
{   
  float width_ratio, height_ratio, resize_ratio;
  float long_side_max  = std::max(max_x, max_y);
  float short_side_max = std::min(max_x, max_y);

  if (width > height)
  { 
    width_ratio  = long_side_max / width;
    height_ratio = short_side_max / height;
  }
  else
  { 
    width_ratio  = short_side_max / height;
    height_ratio = long_side_max / width;
  } 
  resize_ratio = std::min(width_ratio, height_ratio);
  max_x        = height * resize_ratio;
  max_y        = width  * resize_ratio;
}

BasicImage BasicImage::cropped(unsigned int max_x, unsigned max_y, int options)
{
  Magick::Image image(get_filepath());
  BasicImage    copy(*this);

  copy.new_uid();
  if (image.columns() > max_x || image.rows() > max_y)
  {
    if (options & PreserveAspectRatio)
      get_geometry_for_crop_preserving_aspect_ratio(image.columns(), image.rows(), max_x, max_y);
    image.zoom(Magick::Geometry(max_x, max_y));
  }
  image.quality(get_default_image_quality());
  image.magick(extension);
  image.write(copy.get_filepath());
  return copy;
}
