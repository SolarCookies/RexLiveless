// The Guide's panels as glass, when the game has RexGlass: built in when the game attaches RexGlass
// (REXGLUE_GUIDE_WITH_GLASS) and used once the game installs it. Otherwise GlassPanel draws nothing and the
// callers draw their usual flat panels.

#include "guide_dialog.h"

#if REXGLUE_GUIDE_WITH_GLASS
#include <rexglass/panel.h>
#include <rexglass/rexglass.h>
#endif

namespace rexglue_guide {

using namespace ui;

bool GuideDialog::GlassPanel(ImDrawList* dl, ImVec2 p0, ImVec2 p1, float round, ImU32 tint, float tint_alpha, float a, ImDrawFlags corners, bool shadow, bool see_game) {
#if REXGLUE_GUIDE_WITH_GLASS
  if (!rexglass::Installed()) return false;
  const ImVec4 color = ImGui::ColorConvertU32ToFloat4(tint);
  rexglass::Panel panel;
  panel.min = p0;
  panel.max = p1;
  panel.scale = Px(1);
  panel.rounding = round / panel.scale;
  panel.corners = corners;
  panel.tint = ImVec4(color.x, color.y, color.z, tint_alpha);
  panel.frost = 0.85f;
  panel.refraction = 0.6f;
  panel.opacity = a;
  panel.shadow = shadow;
  panel.see_game = see_game;
  // The game as the Guide has it blurred, when the game blurs it for the Guide rather than for RexGlass.
  panel.backdrop = see_game ? glass_backdrop_ : ImTextureID_Invalid;
  panel.backdrop_uv = glass_backdrop_uv_;
  rexglass::AddPanel(dl, panel);
  return true;
#else
  (void)dl, (void)p0, (void)p1, (void)round, (void)tint, (void)tint_alpha, (void)a, (void)corners, (void)shadow, (void)see_game;
  return false;
#endif
}

}  // namespace rexglue_guide
