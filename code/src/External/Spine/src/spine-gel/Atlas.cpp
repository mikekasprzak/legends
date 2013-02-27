#include <Texture/Texture.h>
#include <Search/Search.h>
#include <Core/DataBlock.h>
#include <spine-gel/Atlas.h>

using namespace Texture;

namespace spine {

Atlas::Atlas (std::ifstream &file) {
	load(file);
}

Atlas::Atlas (std::istream &input) {
	load(input);
}

Atlas::Atlas (const std::string &text) {
	load(text);
}

Atlas::Atlas (const char *begin, const char *end) {
	load(begin, end);
}

BaseAtlasPage* Atlas::newAtlasPage (std::string name) {
	AtlasPage *page = new AtlasPage();
	page->texture = new_TextureHandle();
	//page->texture->loadFromFile(name);

	{
		DataBlock* Data = new_read_DataBlock( Search::Search( name.c_str() ) );
		STBTexture Tex = new_STBTexture( Data->Data, Data->Size );
		delete_DataBlock( Data );
		
		Log( "%s -- %i, %i (%i)", name.c_str(), Tex.Width, Tex.Height, Tex.Info );
		
		page->texture = upload_STBTexture( Tex, false, false );
		
		delete_STBTexture( Tex );
	}
	return page;
}

//TODO: delete_TextureHandle( page->texture );

BaseAtlasRegion* Atlas::newAtlasRegion (BaseAtlasPage* page) {
	AtlasRegion *region = new AtlasRegion();
	region->page = reinterpret_cast<AtlasPage*>(page);
	return region;
}

AtlasRegion* Atlas::findRegion (const std::string &name) {
	return reinterpret_cast<AtlasRegion*>(BaseAtlas::findRegion(name));
}

} /* namespace spine */
