#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <optional>
#include <vector>

#include "GameState.h"

// Learned about optionals on cpp
struct ElementsInfo
{
    sf::String text;
    float xAlignn;
    float yAlign;
    std::optional<std::function<void()>> onClick = std::nullopt;
    std::optional<int> fontSize = std::nullopt;
};

/**
 * Base class for all UI menus in the game
 *
 * Menu is responsible for:
 * - Storing text and button elements
 * - Drawing menu elements relative to the current view (centered on the player)
 * - Handling keyboard navigation
 */
class Menu
{
  public:
    /**
     * Create a Menu with elements and initial open state
     *
     * @param elements Text and button descriptions used to create the menu
     * @param windowOpen If true the menu starts open
     */
    Menu(std::vector<ElementsInfo> const &elements, bool windowOpen);
    virtual ~Menu() = default;

    /**
     * Draw the menu if it is open
     *
     * @param window The RenderWindow to draw into
     */
    void draw(sf::RenderWindow *window);

    /**
     * Handle an input event when the menu is open
     * Keyboard navigation and activating the focused button
     *
     * @param event The event to handle
     * @return true if the event was handled
     */
    virtual bool handleEvent(sf::Event const &event);

    /**
     * Check if the menu is currently open
     *
     * @return true if the menu is open
     */
    bool isOpen() const;

  protected:
    /**
     * Set the menu open state
     *
     * @param isOpen New open state
     */
    void setIsOpen(bool isOpen);

    /**
     * Replace all menu elements and rebuild text and button elements
     *
     * @param elements New elements to use for this menu
     */
    void setButtons(std::vector<ElementsInfo> const &elements);

    /**
     * Create menu elements for this menu type
     *
     * @return Vector of ElementsInfo describing the menu elements
     */
    virtual std::vector<ElementsInfo> createButtons() const = 0;

  private:
    /**
     * Set focus highlight on a button by index
     *
     * @param index Index of the button to focus
     */
    void focusButton(int index);

    /**
     * Remove focus highlight from a button by index
     *
     * @param index Index of the button to unfocus
     */
    void unfocusButton(int index);

    /**
     * Change focused button index by a delta
     *
     * @param change Change applied to the current focused index
     */
    void changeFocusedIdx(int change);

    /**
     * Update triangles positions to point to the focused button
     */
    void updateTrianglesPositions();

    int static const DEFAULT_FONT_SIZE;
    float static const DEFAULT_OUTLINE_THICKNESS;
    sf::Vector2f static const DEFAULT_SHADOW_OFFSET;
    float static const TRIANGLE_RADIUS;
    float static const TRIANGLE_OFFSET;

    sf::Color static const TEXT_COLOR;
    sf::Color static const UNFOCUSED_BUTTON_COLOR;
    sf::Color static const FOCUSED_BUTTON_COLOR;
    sf::Color static const OUTLINE_COLOR;

    sf::Font defaultFont;
    std::vector<ElementsInfo> buttonInfos;
    std::vector<sf::Text> textElements;
    std::vector<sf::Text> buttonElements;
    std::vector<sf::Text> shadowElements;
    sf::CircleShape leftTriangle;
    sf::CircleShape rightTriangle;
    sf::Vector2f menuCenter;

    bool menuOpen;
    int focusedButtonIdx;
};

#endif