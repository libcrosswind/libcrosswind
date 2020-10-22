#include <filesystem>

#include "crosswind/composition/tilemap.hpp"

#include "crosswind/composition/core.hpp"
#include "crosswind/graphical/video.hpp"

#include "crosswind/graphical/opengl/texture.hpp"
#include "crosswind/graphical/opengl/renderer.hpp"

#include "crosswind/graphical/object/sprite.hpp"

cw::composition::tilemap::tilemap(std::shared_ptr<cw::composition::core> core, const std::string& path) :
    core(core) {

    auto tilemap_path = std::filesystem::path(path);

	tson::Tileson parser;
	map = std::move(parser.parse(tilemap_path));

    for (auto& tileset : map->getTilesets()) {
        auto image_path = std::filesystem::path(tileset.getImage());
        auto path = tilemap_path.parent_path() / image_path;

        core->video->load_texture(tileset.getImage().string(), path.string());
        auto texture = core->video->load_texture(tileset.getImage().string());

        textures[tileset.getImage().string()] = texture;
    }

    //You can loop through every container of objects
    for (auto& layer : map->getLayers())
    {
        if (layer.getType() == tson::LayerType::ObjectGroup) {
            for (auto& obj : layer.getObjects())
            {
                objects.push_back(obj);
            }
        }

        if (layer.getType() == tson::LayerType::TileLayer)
        {
            for (const auto& [pos, tileObject] : layer.getTileObjects()) {

                for (auto& tileset : map->getTilesets()) {
                    for (const auto& tileset_tile : tileset.getTiles()) {
                        if (tileset_tile.getId() == tileObject.getTile()->getId()) {

                            auto tileset_name = tileset.getImage();
                            auto tile_size = tileset.getTileSize();

                            auto tileset_size = tileset.getImageSize();

                            //auto tileset_tile_drawing_rect = tileset_tile.getDrawingRect();
                            auto tile_drawing_rect = tileObject.getDrawingRect();

                            auto uv_x = (tile_drawing_rect.x) / (float)tileset_size.x;
                            auto uv_y = (1.0f - ((tile_drawing_rect.y) / (float)tileset_size.y));

                            uv_y -= (tile_drawing_rect.height / (float)tileset_size.y);

                            auto uv_z = (tile_drawing_rect.x / (float)tileset_size.x) + 
                                        (tile_drawing_rect.width / (float)tileset_size.x);

                            auto uv_w = (1.0f - (tile_drawing_rect.y / (float)tileset_size.y) +
                                        (tile_drawing_rect.height / (float)tileset_size.y));
                            uv_w -= (tile_drawing_rect.height / (float)tileset_size.y);

                            /*
                            uv_x += 0.5f / (float)tileset_size.x;
                            uv_y -= 0.5f / (float)tileset_size.y;*/

                            auto tile_position = tileObject.getPosition();

                            glm::vec4 uv = glm::vec4(uv_x, uv_y, uv_z, uv_w);

                            glm::vec3 tile_origin = glm::vec3(tile_position.x, tile_position.y * - 1, 0);

                            auto sprite = std::make_shared<cw::graphical::object::sprite>(tile_origin,
                                glm::vec3(tile_size.x, tile_size.y, 0),
                                glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                                uv,
                                textures[tileset_name.string()]->id);

                            sprites.push_back(sprite);

                        }
                    }
                }


                

            }
        }
    }
}

cw::composition::tilemap::~tilemap()
{
    for (auto texturekp : textures) {
        core->video->remove_texture(texturekp.first);
    }
}

void cw::composition::tilemap::draw(std::shared_ptr<cw::graphical::opengl::renderer> renderer) {

    for (auto sprite : sprites) {
        renderer->upload(sprite);
    }
}
