#include <SFML/Graphics.hpp>

#include <sstream>

// Always include the necessary header files.
// Including SFGUI/SFGUI.hpp includes everything
// you can possibly need automatically.
#include <SFGUI/SFGUI.hpp>

sfg::Window::Ptr window;

// This is the first possibility you have of connecting a signal handler.
// You just pass it the address of a normal function:
// button->OnClick.Connect( &Foo );
void Foo() {
	window->SetTitle( "Foo" );
}

class Application {
	public:
		void Run();

		// The second possibility would be defining the function as a class
		// method in the same class as you call Connect() from, in this case
		// Application because Connect() is called from Application::Run.
		// You would pass it the address of the method and the this pointer:
		// button->OnClick.Connect( &Application::Bar, this );
		void Bar();
};

// The definition of the second possibility
void Application::Bar() {
	window->SetTitle( "Bar" );
}

// This is the third possibility. You create instances of a class and
// define their behavior on a per instance basis. Depending on the pointer
// of object you pass to Connect() the same method gets called on different
// objects leading to different behavior.
// You would pass Connect() the method address and a pointer to the object:
// button->OnClick.Connect( &BazClass::Baz, &baz1 );
class BazClass {
	public:
		BazClass( int m_type );
		void Baz();

		int m_type;
};

// In this example we tell the object how it is to behave by setting
// it's type in the constructor.
BazClass::BazClass( int type ) :
	m_type( type )
{
}

void BazClass::Baz() {
	// This is where the object picks how it is going to behave
	// based on it's type.
	switch( m_type ) {
		case 1:
			window->SetTitle( "Baz1" );
			break;
		case 2:
			window->SetTitle( "Baz2" );
			break;
		case 3:
			window->SetTitle( "Baz3" );
			break;
		default:
			break;
	}
}

void Application::Run() {
	sf::RenderWindow app_window( sf::VideoMode( 800, 600 ), "SFGUI Button Example", sf::Style::Titlebar | sf::Style::Close );

	window = sfg::Window::Create();
	window->SetTitle( "Title" );

	sfg::Box::Ptr box = sfg::Box::Create( sfg::Box::VERTICAL );
	window->Add( box );

	// Possibility 1, normal function
	sfg::Button::Ptr button1 = sfg::Button::Create();
	button1->SetLabel( "Clicky 1" );
	button1->OnClick.Connect( &Foo );
	box->Pack( button1, false );

	// Possibility 2, this class
	sfg::Button::Ptr button2 = sfg::Button::Create();
	button2->SetLabel( "Clicky 2" );
	button2->OnClick.Connect( &Application::Bar, this );
	box->Pack( button2, false );

	// Possibility 3, objects
	BazClass baz_array[3] = { BazClass( 1 ), BazClass( 2 ), BazClass( 3 ) };

	for( int i = 0; i < 3; i++ ) {
		std::stringstream sstr;
		sstr << "Clicky " << i + 3;
		sfg::Button::Ptr button = sfg::Button::Create();
		button->SetLabel( sstr.str() );
		// This is just a more complicated way of passing a pointer to a
		// BazClass to Connect() when the BazClass object is part of an array.
		// Passing normal pointers such as &baz1 would also work.
		button->OnClick.Connect( &BazClass::Baz, &( baz_array[i] ) );
		box->Pack( button, false );
	}

	// Notice that with possibility 3 you can do very advanced things. The tricky
	// part of implementing it this way is that the method address has to be
	// known at compile time, which means that only the instanciated object itself
	// is able to pick how it will behave when that method is called on it. This
	// way you can also connect signals to dynamically determined behavior.

	// For further reading on this topic refer to Design Patterns and as
	// specialized cases similar to the one in this example the
	// Factory Method Pattern and Abstract Factory Pattern.

	while ( app_window.isOpen() ) {
		sf::Event event;

		while ( app_window.pollEvent( event ) ) {
			window->HandleEvent( event );

			if ( event.type == sf::Event::Closed ) {
				app_window.close();
			}
		}

		// Update the GUI, note that you shouldn't normally
		// pass 0 seconds to the update method.
		window->Update( 0.f );

		// Clear screen
		app_window.clear();

		// Draw the GUI
		sfg::Renderer::Get().Display( app_window );

		// Update the window
		app_window.display();
	}

	// If you have any global or static widgets,
	// you need to reset their pointers before your
	// application exits.
	window.reset();
}

int main() {
	// Construct our SFML guard
	// See http://sfgui.sfml-dev.de/forum/topic52-crash-on-close.html for more info.
	sfg::SFGUI sfgui;

	// Make sure app is destroyed before the guard.
	{
		Application app;
		app.Run();
	}

	return EXIT_SUCCESS;
}
