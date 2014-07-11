
#ifndef WebThemeControlImpl_h
#define WebThemeControlImpl_h


#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "../../platform/WebNonCopyable.h"
#include "third_party/skia/include/core/SkColor.h"
#include "third_party/skia/include/core/SkRect.h"

using namespace blink;

// Skia forward declarations
class SkCanvas;


class WebThemeControlImpl 
    : public blink::WebNonCopyable
{
public:
    // This list of states mostly mirrors the list in WebCore/platform/ThemeTypes.h
    // but is maintained separately since that isn't public and also to minimize
    // dependencies.
    // Note that the WebKit ThemeTypes seem to imply that a control can be
    // in multiple states simultaneously but WebThemeEngine only allows for
    // a single state at a time.
    //
    // Some definitions for the various states:
    //   Disabled - indicates that a control can't be modified or selected
    //              (corresponds to HTML 'disabled' attribute)
    //   ReadOnly - indicates that a control can't be modified but can be
    //              selected
    //   Normal   - the normal state of control on the page when it isn't
    //              focused or otherwise active
    //   Hot      - when the mouse is hovering over a part of the control,
    //              all the other parts are considered "hot"
    //   Hover    - when the mouse is directly over a control (the CSS
    //               :hover pseudo-class)
    //   Focused  - when the control has the keyboard focus
    //   Pressed  - when the control is being triggered (by a mousedown or
    //              a key event).
    //   Indeterminate - when set to indeterminate (only for progress bar)
    enum State {
        UnknownState = 0,
        DisabledState,
        ReadOnlyState,
        NormalState,
        HotState,
        HoverState,
        FocusedState,
        PressedState,
        IndeterminateState
    };

    // This list of types mostly mirrors the list in
    // WebCore/platform/ThemeTypes.h but is maintained
    // separately since that isn't public and also to minimize dependencies.
    //
    // Note that what the user might think of as a single control can be
    // made up of multiple parts. For example, a single scroll bar contains
    // six clickable parts - two arrows, the "thumb" indicating the current
    // position on the bar, the other two parts of the bar (before and after
    // the thumb) and the "gripper" on the thumb itself.
    //
    enum Type {
        UnknownType = 0,
        TextFieldType,
        PushButtonType,
        UncheckedBoxType,
        CheckedBoxType,
        IndeterminateCheckboxType,
        UncheckedRadioType,
        CheckedRadioType,
        HorizontalScrollTrackBackType,
        HorizontalScrollTrackForwardType,
        HorizontalScrollThumbType,
        HorizontalScrollGripType,
        VerticalScrollTrackBackType,
        VerticalScrollTrackForwardType,
        VerticalScrollThumbType,
        VerticalScrollGripType,
        LeftArrowType,
        RightArrowType,
        UpArrowType,
        DownArrowType,
        HorizontalSliderTrackType,
        HorizontalSliderThumbType,
        VerticalSliderTrackType,
        VerticalSliderThumbType,
        DropDownButtonType,
        ProgressBarType
    };

    // Constructs a control of the given size, type and state to draw
    // on to the given canvas.
    WebThemeControlImpl(SkCanvas*, const SkIRect&, Type, State);
    ~WebThemeControlImpl();

    // Draws the control.
    void draw();

    // Use this for TextField controls instead, because the logic
    // for drawing them is dependent on what WebKit tells us to do.
    // If drawEdges is true, draw an edge around the control. If
    // fillContentArea is true, fill the content area with the given color.
    void drawTextField(bool drawEdges, bool fillContentArea, SkColor);

    // Use this for drawing ProgressBar controls instead, since we
    // need to know the rect to fill inside the bar.
    void drawProgressBar(const SkIRect& fillRect);

private:
    // Draws a box of size specified by irect, filled with the given color.
    // The box will have a border drawn in the default edge color.
    void box(const SkIRect& irect, SkColor);


    // Draws a triangle of size specified by the three pairs of coordinates,
    // filled with the given color. The box will have an edge drawn in the
    // default edge color.
    void triangle(int x0, int y0, int x1, int y1, int x2, int y2, SkColor);

    // Draws a rectangle the size of the control with rounded corners, filled
    // with the specified color (and with a border in the default edge color).
    void roundRect(SkColor);

    // Draws an oval the size of the control, filled with the specified color
    // and with a border in the default edge color.
    void oval(SkColor);

    // Draws a circle centered in the control with the specified radius,
    // filled with the specified color, and with a border draw in the
    // default edge color.
    void circle(SkScalar radius, SkColor);

    // Draws a box the size of the control, filled with the outerColor and
    // with a border in the default edge color, and then draws another box
    // indented on all four sides by the specified amounts, filled with the
    // inner color and with a border in the default edge color.
    void nestedBoxes(int indentLeft, int indentTop, int indentRight, int indentBottom, SkColor outerColor, SkColor innerColor);

    // Draws a line between the two points in the given color.
    void line(int x0, int y0, int x1, int y1, SkColor);

    // Draws a distinctive mark on the control for each state, so that the
    // state of the control can be determined without needing to know which
    // color is which.
    void markState();

    SkCanvas* m_canvas;
    const SkIRect m_irect;
    const Type m_type;
    const State m_state;
    const SkColor m_edgeColor;
    const SkColor m_bgColor;
    const SkColor m_fgColor;

    // The following are convenience accessors for m_irect.
    const int m_left;
    const int m_right;
    const int m_top;
    const int m_bottom;
    const int m_width;
    const int m_height;
};


#endif // 
