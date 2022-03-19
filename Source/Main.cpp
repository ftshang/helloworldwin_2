/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainComponent.h"

/* struct Bag
{
    Bag(int howMuchStuffToHold) {}
};
*/

struct Person {
    int age = 0;
    //Bag age;
    int heightInInches{ 0 }, distanceTraveled{ 0 };
    float hairLength, GPA{ 0.f };
    unsigned int SATScore{ 0 };
    juce::String name;

    // Another Constructor
    Person(juce::String personsName) : name{personsName} 
    {
        DBG("Person constructor: " + name);
    }

    // Constructor
    // Person();

    // Destructor
    ~Person() 
    {
        DBG("Person destructor: " + name);
    }
};

void PersonFunction()
{
    Person p{ "cool" }; // When this goes out of scope, then its Destructor gets called: ~Person().
    // After the Destructor finishes executing, p's member variables get destroyed
}

//Person::Person() : age{ 4 } {}

struct IntValue
{
    // Constructor
    IntValue() 
    {
        DBG("IntValue Constructor");
    }
    // Destructor
    ~IntValue()
    {
        DBG("IntValue Destructor");
    }

    // Member variable
    int value;
};

int functionA(int val)
{
    IntValue a;
    a.value = 5;
    return val * 2 + a.value;
}

void functionB()
{
    IntValue val;
    val.value = functionA(3);
    val.value *= 4;
}

void functionC()
{
    int i = 0;
    while (i < 3)
    {
        IntValue a;
        a.value += i;
        i += 1; 
    }
    DBG(i);
    for (int i = 0; i <= 4; i += 1)
    {
        IntValue a;
        DBG(i);
        a.value += i;
    }
    DBG(i);
}

void functionD()
{
    int i = 0;
    int total = 10;
    while (i < 3)
    {
        total += i;
        i++;
    }
}

void functionE()
{
    int a = 0;
    a += 1;
    {
        a = 2;
        int a = 4;
        a += 1;
        DBG(a);
    }
    DBG(a);
}

struct Family 
{
    Person mom{ "mom" };
    Person dad{ "dad" };
    Person child1{ "helen" };
    Person child2{ "frank" };

    // Constructor
    Family()
    {
        DBG("Family constructor!");
    }

    // Destructor
    ~Family()
    {
        DBG("Family destructor!");
    }
};

void familyFunction()
{
    Family family;
}

//==============================================================================
class HelloWorldApplication  : public juce::JUCEApplication
{
public:
    //==============================================================================
    HelloWorldApplication() {}

    const juce::String getApplicationName() override       { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    //==============================================================================
    void initialise (const juce::String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..
        familyFunction();
        mainWindow.reset (new MainWindow (getApplicationName()));
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const juce::String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    class MainWindow    : public juce::DocumentWindow
    {
    public:
        MainWindow (juce::String name)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (juce::ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);

           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
           #else
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());
           #endif

            setVisible (true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (HelloWorldApplication)
