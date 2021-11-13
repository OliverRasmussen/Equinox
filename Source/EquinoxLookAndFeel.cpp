/*
  ==============================================================================

    EquinoxLookandFeel.cpp
    Created: 31 Jul 2021 12:03:51am
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "EquinoxLookAndFeel.h"


EquinoxLookAndFeel::EquinoxLookAndFeel()
{
    rotaryKnob = ImageCache::getFromMemory(BinaryData::RotaryKnob_png, BinaryData::RotaryKnob_pngSize);
    rotaryKnobShadow = ImageCache::getFromMemory(BinaryData::RotaryKnobShadow_png, BinaryData::RotaryKnobShadow_pngSize);

    sliderKnob = ImageCache::getFromMemory(BinaryData::SmallSliderKnob_png, BinaryData::SmallSliderKnob_pngSize);
    sliderLine = ImageCache::getFromMemory(BinaryData::SliderLine_png, BinaryData::SliderLine_pngSize);
    
    buttonUp = ImageCache::getFromMemory(BinaryData::BtnUp1_png, BinaryData::BtnUp1_pngSize);
    buttonDown = ImageCache::getFromMemory(BinaryData::BtnDown1_png, BinaryData::BtnDown1_pngSize);
}


EquinoxLookAndFeel::~EquinoxLookAndFeel()
{
    
}

void EquinoxLookAndFeel::drawButtonBackground (Graphics& g,
                                               Button& button,
                                               const Colour& backgroundColour,
                                               bool shouldDrawButtonAsHighlighted,
                                               bool shouldDrawButtonAsDown)
{
    auto btnBounds = button.getLocalBounds().toFloat();


    Image btnBackground = shouldDrawButtonAsDown ? buttonDown : buttonUp;
    
    g.drawImage(btnBackground, btnBounds);
}

void EquinoxLookAndFeel::drawButtonText (Graphics& g,
                                         TextButton& button,
                                         bool shouldDrawButtonAsHighlighted,
                                         bool shouldDrawButtonAsDown)
{
    Font font (getTextButtonFont (button, button.getHeight()));
    g.setFont (font);
    
    g.setColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                    : TextButton::textColourOffId)
                 .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));
    
    float widthMultiplier = 1.0f;
    float xPosMultiplier = 1.0f;
    
    if (shouldDrawButtonAsDown)
    {
        widthMultiplier = 0.98f;
        xPosMultiplier += 1 - widthMultiplier;
        g.setColour(button.findColour(TextButton::textColourOnId).darker(0.15f));
        g.setColour(button.findColour(TextButton::textColourOffId).darker(0.15f));
    }

    const int yIndent = jmin (4, button.proportionOfHeight (0.3f));
    const int cornerSize = jmin (button.getHeight(), button.getWidth()) / 2;

    const int fontHeight = roundToInt (font.getHeight() * 0.6f);
    const float leftIndent  = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
    const float rightIndent = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
    const float textWidth = (button.getWidth() - leftIndent - rightIndent) * widthMultiplier;

    if (textWidth > 0)
        g.drawFittedText (button.getButtonText(),
                          leftIndent * xPosMultiplier, yIndent, textWidth, button.getHeight() - yIndent * 2,
                          Justification::centred, 2);
}

void EquinoxLookAndFeel::drawLinearSlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider)
{
    float lineCentreX = x + width * 0.5f - sliderLine.getWidth() * 0.5f;
    
    float knobCentreX = x + width * 0.5f - sliderKnob.getWidth()/2;

    float knobCentreY = sliderKnob.getHeight() * 0.5f;
    
    float knobPos = sliderPos - knobCentreY;
    
    Rectangle<float> sliderLineRect (lineCentreX, (float)y-10, (float)sliderLine.getWidth(), (float)height+17);
    g.drawImage(sliderLine, sliderLineRect);

    g.drawImageAt(sliderKnob, knobCentreX, knobPos);
}


void EquinoxLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    
    
    Image knob = rotaryKnob.rescaled(width - 15, height - 15);
    
    float centreX = width * 0.5f;

    float rotaryKnobCentreX = (float)knob.getWidth() * 0.5f;
    float rotaryKnobCentreY = (float)knob.getHeight() * 0.5f;
    float rotation = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle) - MathConstants<float>::pi;
    
    AffineTransform transform;
    float knobPosX = centreX - rotaryKnobCentreX;
    float knobPosY = 7;

    transform = transform.rotation(rotation, rotaryKnobCentreX, rotaryKnobCentreY).translated(knobPosX, knobPosY);

    
    g.drawImage(rotaryKnobShadow, {knobPosX, knobPosY + 5, (float)knob.getWidth(), (float)knob.getHeight()});
    
    g.drawImageTransformed(knob, transform, false);
    
}

void EquinoxLookAndFeel::drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown)
{
    const Rectangle<int> activeArea (button.getActiveArea());

    const TabbedButtonBar::Orientation o = button.getTabbedButtonBar().getOrientation();

    //const Colour bkg (button.getTabBackgroundColour());

    const Colour bkg (Colours::black);
    
    if (button.getToggleState())
    {
        g.setColour (bkg);
    }
    else
    {
        Point<int> p1, p2;

        switch (o)
        {
            case TabbedButtonBar::TabsAtBottom:   p1 = activeArea.getBottomLeft(); p2 = activeArea.getTopLeft();    break;
            case TabbedButtonBar::TabsAtTop:      p1 = activeArea.getTopLeft();    p2 = activeArea.getBottomLeft(); break;
            case TabbedButtonBar::TabsAtRight:    p1 = activeArea.getTopRight();   p2 = activeArea.getTopLeft();    break;
            case TabbedButtonBar::TabsAtLeft:     p1 = activeArea.getTopLeft();    p2 = activeArea.getTopRight();   break;
            default:                              jassertfalse; break;
        }

        g.setGradientFill (ColourGradient (bkg.brighter (0.2f), p1.toFloat(),
                                           bkg.darker (0.1f),   p2.toFloat(), false));
    }

    g.fillRect (activeArea);

    g.setColour (button.findColour (TabbedButtonBar::tabOutlineColourId));

    Rectangle<int> r (activeArea);

    if (o != TabbedButtonBar::TabsAtBottom)   g.fillRect (r.removeFromTop (1));
    if (o != TabbedButtonBar::TabsAtTop)      g.fillRect (r.removeFromBottom (1));
    if (o != TabbedButtonBar::TabsAtRight)    g.fillRect (r.removeFromLeft (1));
    if (o != TabbedButtonBar::TabsAtLeft)     g.fillRect (r.removeFromRight (1));

    const float alpha = button.isEnabled() ? ((isMouseOver || isMouseDown) ? 1.0f : 0.8f) : 0.3f;

    Colour col (bkg.contrasting().withMultipliedAlpha (alpha));

    if (TabbedButtonBar* bar = button.findParentComponentOfClass<TabbedButtonBar>())
    {
        TabbedButtonBar::ColourIds colID = button.isFrontTab() ? TabbedButtonBar::frontTextColourId
                                                               : TabbedButtonBar::tabTextColourId;

        if (bar->isColourSpecified (colID))
            col = bar->findColour (colID);
        else if (isColourSpecified (colID))
            col = findColour (colID);
    }

    const Rectangle<float> area (button.getTextArea().toFloat());

    float length = area.getWidth();
    float depth  = area.getHeight();

    if (button.getTabbedButtonBar().isVertical())
        std::swap (length, depth);

    TextLayout textLayout;
    createTabTextLayout (button, length, depth, col, textLayout);

    AffineTransform t;

    switch (o)
    {
        case TabbedButtonBar::TabsAtLeft:   t = t.rotated (MathConstants<float>::pi * -0.5f).translated (area.getX(), area.getBottom()); break;
        case TabbedButtonBar::TabsAtRight:  t = t.rotated (MathConstants<float>::pi *  0.5f).translated (area.getRight(), area.getY()); break;
        case TabbedButtonBar::TabsAtTop:
        case TabbedButtonBar::TabsAtBottom: t = t.translated (area.getX(), area.getY()); break;
        default:                            jassertfalse; break;
    }

    g.addTransform (t);
    textLayout.draw (g, Rectangle<float> (length, depth));
}
