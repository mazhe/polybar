#pragma once

#include "modules/meta/event_module.hpp"
#include "modules/meta/types.hpp"
#include "settings.hpp"

POLYBAR_NS

// fwd
namespace oss {
  class mixer;
}  // namespace oss

namespace modules {
  using mixer_t = shared_ptr<oss::mixer>;

  class oss_module : public event_module<oss_module> {
   public:
    explicit oss_module(const bar_settings&, string, const config&);

    void teardown();
    bool has_event();
    bool update();
    string get_format() const;
    string get_output();
    bool build(builder* builder, const string& tag) const;

    static constexpr auto TYPE = OSS_TYPE;

    static constexpr auto EVENT_INC = "inc";
    static constexpr auto EVENT_DEC = "dec";
    static constexpr auto EVENT_TOGGLE = "toggle";

   protected:
    void action_inc();
    void action_dec();
    void action_toggle();

    void change_volume(int interval);

    void action_epilogue();

   private:
    static constexpr auto FORMAT_VOLUME = "format-volume";
    static constexpr auto FORMAT_MUTED = "format-muted";

    static constexpr auto TAG_RAMP_VOLUME = "<ramp-volume>";
    static constexpr auto TAG_BAR_VOLUME = "<bar-volume>";
    static constexpr auto TAG_LABEL_VOLUME = "<label-volume>";
    static constexpr auto TAG_LABEL_MUTED = "<label-muted>";

    progressbar_t m_bar_volume;
    ramp_t m_ramp_volume;
    label_t m_label_volume;
    label_t m_label_muted;

    mixer_t m_mixer;
    bool m_unmute_on_scroll{false};
    int m_interval{5};
    atomic<bool> m_muted{false};
    atomic<int> m_volume{0};
  };
}  // namespace modules

POLYBAR_NS_END