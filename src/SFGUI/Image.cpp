#include <SFGUI/Image.hpp>
#include <SFGUI/Context.hpp>
#include <SFGUI/Engine.hpp>

#include <SFML/Graphics/Image.hpp>

namespace sfg {

Image::Image( const sf::Image& image ) :
	Misc()
{
	SetAlignment( sf::Vector2f( .5f, .5f ) );
	SetImage( image );
}

Image::~Image() {
}

Image::Ptr Image::Create( const sf::Image& image ) {
	Ptr image_ptr( new Image( image ) );
	return image_ptr;
}

void Image::SetImage( const sf::Image& image ) {
	if( image.getWidth() && image.getHeight() ) {
		m_image = image;
		m_texture.loadFromImage( m_image );
	}

	RequestResize();
	Invalidate();
}

const sf::Image& Image::GetImage() const {
	return m_image;
}

const sf::Texture& Image::GetTexture() const {
	return m_texture;
}

RenderQueue* Image::InvalidateImpl() const {
	return Context::Get().GetEngine().CreateImageDrawable( DynamicPointerCast<const Image>( shared_from_this() ) );
}

sf::Vector2f Image::CalculateRequisition() {
	return sf::Vector2f( static_cast<float>( m_image.getWidth() ), static_cast<float>( m_image.getHeight() ) );
}

const std::string& Image::GetName() const {
	static const std::string name( "Image" );
	return name;
}

}
