/// @file
/// @brief Describes interface for all window implementations.
/// @author Fedorov Alexey
/// @date 05.04.2017

#ifndef FRAMEWORK_GRAPHIC_WINDOW_IMPLEMENTATION_HPP
#define FRAMEWORK_GRAPHIC_WINDOW_IMPLEMENTATION_HPP

#include <memory>
#include <string>
#include <vector>

#include <graphic/window.hpp>

namespace framework
{
namespace graphic
{
class window::implementation
{
public:
    static std::unique_ptr<implementation> create(window::size_t size, const std::string& title);

    implementation()          = default;
    virtual ~implementation() = default;

    implementation(const implementation&) = delete;
    implementation& operator=(const implementation&) = delete;

    /// @name actions
    /// @{
    virtual void show()           = 0;
    virtual void hide()           = 0;
    virtual void focus()          = 0;
    virtual void process_events() = 0;

    virtual void iconify()              = 0;
    virtual void maximize()             = 0;
    virtual void switch_to_fullscreen() = 0;
    virtual void restore()              = 0;
    /// @}

    /// @name setters
    /// @{
    virtual void set_size(size_t)         = 0;
    virtual void set_position(position_t) = 0;

    virtual void set_max_size(size_t) = 0;
    virtual void set_min_size(size_t) = 0;

    virtual void set_resizable(bool) = 0;

    virtual void set_title(const std::string& title) = 0;
    /// @}

    /// @name getters
    /// @{
    virtual position_t position() const = 0;
    virtual size_t size() const         = 0;

    virtual size_t max_size() const = 0;
    virtual size_t min_size() const = 0;

    virtual std::string title() const = 0;

    virtual uint64 native_handler() const = 0;
    /// @}

    /// @name state
    /// @{
    virtual bool fullscreen() const = 0;
    virtual bool iconified() const  = 0;
    virtual bool maximized() const  = 0;
    virtual bool resizable() const  = 0;
    virtual bool visible() const    = 0;
    virtual bool focused() const    = 0;
    /// @}
};

} // namespace graphic

} // namespace framework

#endif
