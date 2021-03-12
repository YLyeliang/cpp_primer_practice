//
// Created by fiberhome on 2021/3/12.
//

#include "iostream"
#include "sstream"
#include "fstream"
#include "string"

using namespace std;


// The IO library revisited
// In this chapter we'll look at three of the more specialized features: format control, unformatted IO, random access


int main() {
    // there are a set of manipulators
    // endl is one of it: It writes a newline and flushes the buffer

    // Many Manipulators change the format state
    // Manipulators that change the format state of the stream usually leave the format state changed for all subsequent IO

    // Controlling the format of boolean values
    // By default, bool values print 0 or 1. We can override this by applying the boolalpha to the stream:
    cout << "default bool values: " << true << " " << false
         << "\nalpha bool values: " << boolalpha
         << true << " " << false << endl;
    // once we "write" boolapha on cout, we've changed how cout will print bool values from this point on.
    // To undo this format, apply noboolapha
    bool bool_val = true;
    cout << boolalpha // sets the internal state of cout
         << bool_val
         << noboolalpha; // resets the internal state to default formatting

    // Specifying the base for integral values
    cout << "default: " << 20 << " " << 1024 << endl;
    cout << "octal: " << oct << 20 << " " << 1024 << endl;
    cout << "hex: " << hex << 20 << " " << 1024 << endl;
    cout << "decimal:" << dec << 20 << " " << 1024 << endl;

    // Indicating base on the output
    // A leading 0x indicates hexadecimal
    // ... 0 indicates octal
    // The absence of either indicates decimal
    cout << showbase; // show the base when printing integral values
    cout << "default: " << 20 << " " << 1024 << endl;
    cout << "in octal: " << oct << 20 << " " << 1024 << endl;
    cout << "in hex: " << hex << 20 << " " << 1024 << endl;
    cout << "in decimal: " << dec << 20 << " " << 1024 << endl;
    cout << noshowbase; // reset the state of the stream
    // default hexadecimal values are printed in lowercase. We can use uppercase manipulator to print uppercase
    cout << uppercase << showbase << hex
         << "printed in hexadecimal: " << 20 << " " << 1024
         << nouppercase << noshowbase << dec << endl;

    // Controlling the format of floating-point values
    // three aspects of floating-point output:
    // how many digits of precision
    // whether the number is printed in hexadecimal, fixed decimal, or scientific notation
    // Whether a decimal point is printed for floating-point values that are whole numbers

    // Specifying how much precision to print
    // by calling the precision member of an IO object or using the setprecision manipulator,
    // setprecision and other manipulators defined in iomanip header.
    // cout.precision reports the current precision value
    cout << "Precision: " << cout.precision()
         << ", Value: " << sqrt(2.0) << endl;
    // cout.precision(12) asks that 12 digits of precision be printed
    cout.precision(12);
    cout << "Precision: " << cout.precision()
         << ", Value: " << sqrt(2.0) << endl;
    // alternative way to set precision using the setprecision manipulator
    cout << setprecision(3);
    cout << "Precision: " << cout.precision()
         << ", Value: " << sqrt(2.0) << endl;

    // Specifying the notation of floating-point numbers
    // The scientific manipulator change the stream to use scientific notation. fixed ... use fixed decimal
    // hexfloat ... .  defaultfloat ...
    cout << "default format: " << 100 * sqrt(2.0) << '\n'
         << "scientific: " << scientific << 100 * sqrt(2.0) <<
         '\n'
         << "fixed decimal: " << fixed << 100 * sqrt(2.0) <<
         '\n'
         << "hexadecimal: " << hexfloat << 100 * sqrt(2.0) <<
         '\n'
         << "use defaults: " << defaultfloat << 100 * sqrt(2.0)
         << "\n\n";

    // Printing the decimal point
    // showpoint
    cout << 10.0 << endl;
    cout << showpoint << 10.0 << noshowpoint << endl;

    // Padding the output
    // setw to specify the minimum space for the next numeric or string value
    // left to left-justify the output
    // right to right-justify ... which is default.
    // internal controls placement of the sign on negative values. It left-justify the sign and right-justify the value,
    // padding any intervening space with blanks.
    // setfill let us specify an alternative character to use to pad the output. Default is space
    // note: setw is like endl, doesn't change the intelnal state of the output stream, It only determine the next.
    int i = -16;
    double d = 3.14159;
    // pad the first column to use a minimum of 12 positions in the output
    cout << "i: " << setw(12) << i << "next col" << '\n'
         << "d: " << setw(12) << d << "next col" << '\n';
    // pad the first column and left-justify all columns
    cout << left
         << "i: " << setw(12) << i << "next col" << '\n'
         << "d: " << setw(12) << d << "next col" << '\n'
         << right; // restore normal justification
    // pad the first column and right-justify all columns
    cout << right
         << "i: " << setw(12) << i << "next col" << '\n'
         << "d: " << setw(12) << d << "next col" << '\n';
    // pad the first column but put the padding internal to the field
    cout << internal
         << "i: " << setw(12) << i << "next col" << '\n'
         << "d: " << setw(12) << d << "next col" << '\n';
    // pad the first column, using # as the pad character
    cout << setfill('#')
         << "i: " << setw(12) << i << "next col" << '\n'
         << "d: " << setw(12) << d << "next col" << '\n'
         << setfill(' '); // restore the normal pad character

    // controlling input formatting
    // Default, the input operator ignore whitespace(blank, tab, newline, formfeed, carriage return(Enter))
    char ch;
    while (cin >> ch)
        cout << ch;
    // given
    // a b    c
    // d
    // which skipping the intervening blanks, possible tabs, and newline characters. The results is abcd
    // The noskipws manipulators causes the input to read.
    cin >> noskipws;
    cin >> skipws;  // reset

    // 175.2 Unformatted IO operations
    // Single-Byte operations
    while (cin.get(ch))
        cout.put(ch);
    // preserves the whitespace in the input. output is identical to the input. the same as the program using noskipws

    // Putting back onto an input stream
    // sometimes we need to read a character in order to know that we aren't ready for it.
    // peek returns a copy of the next character on the input stream but doesn't change it. The value returned by peek
    // stays on the stream.
    // unget backs up the input stream so that value last returned is still on the stream.
    // putback is a specialized version of unget: returns the last value read from the stream but takes an argument that
    // must be the same as the one that was last read.

    // int return values from input operations
    int ch2;
    // loop to read and write all the data in the input
    while ((ch = cin.get()) != EOF)
        cout.put(ch);

    // Multi-Byte Operations
    // is.get() is.getline() is.read() is.gcount() os.write() is.ignore()
    // call gcount to determine how many characters the last unformatted input operation read.

    // 175.3 Random access to a stream
    // Note: random IO is an inherently system-dependent.

    // seek and tell function
    // g: getting, p: putting

    // Repositioning the marker
    // two versions of the seek function: one moves to the "absolute" address within the file;
    // the other moves to a byte offset from a given position.
    // set the marker to a fixed position
//    seekg(new_position);    // set the read maker to the given pos_type position
//    seekp(new_position);    // set the write marker to the ...

    // offset some distance ahead of or behind the given starting point
//    seekg(offset, from);    // set the read ... offset distance from `from`.
//    seekp(offset, from);    // offset has type off_type

    // remember the current write position in mark
    ostringstream writeStr; // output stringstream
    ostringstream::pos_type mark = writeStr.tellp();
    // ...
    if (cancelEntry)
        // return to the remembered position
        writeStr.seekp(mark);

    // Reading and writing to the same file
    // assume given a file to read. write a newline at the end of the file that contains the relative position at which
    // each line begins. // i.e.
    // abcd
    // efg
    // hi
    // j
    // program produce the following:
    // abcd
    // efg
    // hi
    // j5
    // 9 12 14


}
