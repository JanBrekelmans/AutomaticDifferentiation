#pragma once

#include <memory>

namespace Streams {

    template<typename T>
    class StreamProvider;

    template <typename T>
    class Stream;

    template<typename T>
    using StreamProviderPointer = std::unique_ptr<StreamProvider<T>>;
}  // namespace Streams