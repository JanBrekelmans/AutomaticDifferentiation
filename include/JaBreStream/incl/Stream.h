#pragma once

#include <functional>
#include <memory>
#include <optional>

namespace Streams {

    template <typename T>
    class Stream {
      public:
        Stream(const Stream&) = delete;

        using Type = T;

      private:
        StreamProviderPointer<T> source_;
    };

}  // namespace Streams