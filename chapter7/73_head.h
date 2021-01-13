
//
// Created by fiberhome on 2020/12/15.
//

#ifndef NOW_CODE_73_HEAD_H
#define NOW_CODE_73_HEAD_H

#include "utility"
#include "string"
#include "vector"

class Window_mgr;

class Screen {
public:

    // Window_mgr members can access the private parts of class Screen.
//    friend class Window_mgr;
    // only set the member function to friend.
    // clear must be declared before the Screen.
    friend void Window_mgr::clear(ScreenIdx);

    typedef std::string::size_type pos;

    void some_member() const; // mutable member

    Screen &set(char);

    Screen &set(pos, pos, char);

    Screen &display(std::ostream &os) {
        do_display(os);
        return *this;
    }

    const Screen &display(std::ostream &os) const {
        do_display(os);
        return *this;
    }

    // equivalent to below
//    using pos = std::string::size_type;

    //Because we have provided a constructor, the compiler will not
    //automatically generate a default constructor for us. If our class is to have
    //a default constructor, we must say so explicitly.
    Screen() = default; // needed because Screen has another constructor
    // Cursor initialized to 0 by in-class initializer.
    Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht * wd, c) {}

    char get() const { return contents[cursor]; } //implicitly inline
    inline char get(pos ht, pos wd) const; // explicitly inline
    Screen &move(pos r, pos c); // can be made inline later

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;

    void do_display(std::ostream &os) const { os << contents; }

    mutable size_t access_ctr; // may change even in a const object
//    std::vector<Screen> screens{Screen(24, 80, '')}; //

};

inline Screen &Screen::set(char c) {
    contents[cursor] = c; // set new value at current location.
    return *this;
}

inline Screen &Screen::set(pos r, pos c, char ch) {
    contents[r * width + c] = ch;
    return *this;
}

void Screen::some_member() const {
    ++access_ctr; // if not mutable ,error happened.
}

// specify inline only outside the class make it easier to read.
inline  // we can specify inline on the definition
Screen &Screen::move(pos r, pos c) {
    pos row = r * width; // compute the row location in flatten way
    cursor = row + c;
    return *this;
}

char Screen::get(pos r, pos c) const { // declare as inline in the class
    pos row = r * width;
    return contents[row + c];

}

// If clear were not a friend of Screen, this code would not compile
// note: friendship is not transitive, the friends of Window_mgr can't
// access the Screen.
class Window_mgr {
public:
    using ScreenIdx = std::vector<Screen>::size_type;

    // reset the Screen at the given position to all blanks
    void clear(ScreenIdx);

private:
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};

void Window_mgr::clear(ScreenIdx i) {
    // s is a reference to the screen we want to clear
    Screen &s = screens[i];
    // reset the contents of that screen to all blanks
    s.contents = std::string(s.height * s.width, ' ');
}


#endif //NOW_CODE_73_HEAD_H
