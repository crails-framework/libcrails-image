#ifndef  CRAILS_IMAGE_HPP
# define CRAILS_IMAGE_HPP

# include <crails/attachment.hpp>
# include <utility>
# include <cstddef>

namespace Crails
{
  class BasicImage : public Attachment
  {
  public:
    enum Option
    {
      NoOption = 0,
      PreserveAspectRatio
    };

    BasicImage()
    {
    }

    BasicImage(const std::string& uid) : Attachment(uid)
    {
    }

    virtual unsigned short get_default_image_quality() const
    {
      return 85;
    }

    std::pair<std::size_t, std::size_t> size() const;
    BasicImage resized(unsigned int x, unsigned int y, int options = NoOption);
    BasicImage cropped(unsigned int max_x, unsigned int max_y, int options = NoOption);
  };
}

#endif
