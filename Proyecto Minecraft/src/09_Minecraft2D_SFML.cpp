#include <SFML/Graphics.hpp>
#include <array>
#include <map>
#include <string>
#include <vector>

// Ejemplo 2D tipo "Minecraft" usando SFML
// Controles:
// - Flechas / WASD: mover
// - X o click izquierdo: picar (quita bloque frente al jugador)
// - C o click derecho: construir (coloca bloque seleccionado frente al jugador)
// - 1..5: seleccionar tipo de bloque
// - Esc: salir

const int W = 20;
const int H = 12;
const int TILE = 32;

enum Block : char { AIR = ' ', GRASS = 'G', DIRT = 'D', STONE = 'S', WOOD = 'W', BEDR = 'B' };

using World = std::vector<std::string>;

struct Player {
    int x, y;
    int fx, fy; // facing direction
    char selected;
    std::map<char,int> inv;
};

void init_world(World &world) {
    world.assign(H, std::string(W, (char)AIR));
    int ground = H - 4;
    for (int y = ground; y < H-1; ++y) {
        for (int x = 0; x < W; ++x) {
            if (y == ground) world[y][x] = (char)GRASS;
            else if (y < H-2) world[y][x] = (char)DIRT;
            else world[y][x] = (char)STONE;
        }
    }
    for (int x = 0; x < W; ++x) world[H-1][x] = (char)BEDR;
    // simple árbol
    int tx = 4, ty = ground - 1;
    if (ty-2 >= 0) {
        world[ty][tx] = (char)WOOD;
        world[ty-1][tx] = (char)WOOD;
        world[ty-2][tx] = (char)WOOD;
    }
}

bool in_bounds(int x,int y){ return x>=0 && x<W && y>=0 && y<H; }

char get_block(const World &w, int x,int y){ if(!in_bounds(x,y)) return (char)BEDR; return w[y][x]; }
void set_block(World &w,int x,int y,char b){ if(in_bounds(x,y)) w[y][x]=b; }

int main(){
    World world;
    init_world(world);

    Player p{};
    p.x = W/2; p.y = H-5; p.fx = 1; p.fy = 0; p.selected = (char)GRASS;
    p.inv[(char)GRASS]=5; p.inv[(char)DIRT]=5; p.inv[(char)STONE]=3; p.inv[(char)WOOD]=2; p.inv[(char)BEDR]=0;

    sf::RenderWindow window(sf::VideoMode(W*TILE, H*TILE + 80), "Minecraft2D - SFML");
    window.setFramerateLimit(60);

    // colores para bloques
    std::map<char, sf::Color> color {
        {(char)AIR, sf::Color(135,206,235)}, // sky
        {(char)GRASS, sf::Color(88, 166, 72)},
        {(char)DIRT, sf::Color(134, 96, 67)},
        {(char)STONE, sf::Color(120,120,120)},
        {(char)WOOD, sf::Color(150, 111, 51)},
        {(char)BEDR, sf::Color(40,40,40)}
    };

    // load font from assets
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/Minecraft.ttf")) {
        // fallback to system font may fail; proceed without text if unavailable
    }

    sf::RectangleShape tile(sf::Vector2f(TILE, TILE));
    sf::RectangleShape playerShape(sf::Vector2f(TILE-6, TILE-6));
    playerShape.setFillColor(sf::Color::Yellow);

    while (window.isOpen()){
        sf::Event ev;
        while (window.pollEvent(ev)){
            if (ev.type == sf::Event::Closed) window.close();
            if (ev.type == sf::Event::KeyPressed){
                if (ev.key.code == sf::Keyboard::Escape) window.close();
                if (ev.key.code == sf::Keyboard::A || ev.key.code == sf::Keyboard::Left) { if (p.x>0) p.x--; p.fx=-1; p.fy=0; }
                if (ev.key.code == sf::Keyboard::D || ev.key.code == sf::Keyboard::Right) { if (p.x<W-1) p.x++; p.fx=1; p.fy=0; }
                if (ev.key.code == sf::Keyboard::W || ev.key.code == sf::Keyboard::Up) { if (p.y>0) p.y--; p.fx=0; p.fy=-1; }
                if (ev.key.code == sf::Keyboard::S || ev.key.code == sf::Keyboard::Down) { if (p.y<H-1) p.y++; p.fx=0; p.fy=1; }
                if (ev.key.code == sf::Keyboard::X) {
                    int tx = p.x + p.fx, ty = p.y + p.fy;
                    if (in_bounds(tx,ty)){
                        char b = get_block(world,tx,ty);
                        if (b!=(char)AIR && b!=(char)BEDR) { p.inv[b]++; set_block(world,tx,ty,(char)AIR); }
                    }
                }
                if (ev.key.code == sf::Keyboard::C) {
                    int tx = p.x + p.fx, ty = p.y + p.fy;
                    char b = p.selected;
                    if (in_bounds(tx,ty) && get_block(world,tx,ty)==(char)AIR && p.inv[b]>0) { p.inv[b]--; set_block(world,tx,ty,b); }
                }
                if (ev.key.code >= sf::Keyboard::Num1 && ev.key.code <= sf::Keyboard::Num5) {
                    int idx = ev.key.code - sf::Keyboard::Num1;
                    char mapSel[5] = {(char)GRASS,(char)DIRT,(char)STONE,(char)WOOD,(char)BEDR};
                    p.selected = mapSel[idx];
                }
            }
            if (ev.type == sf::Event::MouseButtonPressed){
                sf::Vector2i m = sf::Mouse::getPosition(window);
                int mx = m.x / TILE; int my = m.y / TILE;
                if (ev.mouseButton.button == sf::Mouse::Left){
                    // picar el tile clicado
                    if (in_bounds(mx,my)){
                        char b = get_block(world,mx,my);
                        if (b!=(char)AIR && b!=(char)BEDR){ p.inv[b]++; set_block(world,mx,my,(char)AIR); }
                    }
                } else if (ev.mouseButton.button == sf::Mouse::Right){
                    // colocar bloque seleccionado en el tile clicado si está vacío
                    if (in_bounds(mx,my)){
                        char b = p.selected;
                        if (get_block(world,mx,my)==(char)AIR && p.inv[b]>0){ p.inv[b]--; set_block(world,mx,my,b); }
                    }
                }
            }
        }

        window.clear(sf::Color(135,206,235));

        // draw world
        for (int y=0;y<H;++y){
            for (int x=0;x<W;++x){
                char b = get_block(world,x,y);
                sf::Color col = color.count(b) ? color[b] : sf::Color::Magenta;
                tile.setPosition(x*TILE, y*TILE);
                tile.setFillColor(col);
                window.draw(tile);
                // grid lines
                sf::RectangleShape gline(sf::Vector2f(TILE-1,1));
                gline.setPosition(x*TILE, y*TILE);
                gline.setFillColor(sf::Color(0,0,0,30));
            }
        }

        // draw player
        playerShape.setPosition(p.x*TILE + 3, p.y*TILE + 3);
        window.draw(playerShape);

        // HUD background
        sf::RectangleShape hudBg(sf::Vector2f(W*TILE, 80));
        hudBg.setPosition(0, H*TILE);
        hudBg.setFillColor(sf::Color(30,30,30,200));
        window.draw(hudBg);

        // draw inventory squares and text
        for (int i=0;i<5;++i){
            char mapSel[5] = {(char)GRASS,(char)DIRT,(char)STONE,(char)WOOD,(char)BEDR};
            char b = mapSel[i];
            sf::RectangleShape slot(sf::Vector2f(48,48));
            slot.setPosition(10 + i*60, H*TILE + 16);
            slot.setFillColor(color[b]);
            if (b==p.selected) {
                slot.setOutlineThickness(3);
                slot.setOutlineColor(sf::Color::Yellow);
            } else {
                slot.setOutlineThickness(1);
                slot.setOutlineColor(sf::Color::Black);
            }
            window.draw(slot);

            // count
            if (font.getInfo().family.size() > 0) {
                sf::Text t(std::to_string(p.inv[b]), font, 16);
                t.setFillColor(sf::Color::White);
                t.setPosition(10 + i*60 + 28, H*TILE + 48);
                window.draw(t);
            }
        }

        // instructions
        if (font.getInfo().family.size() > 0) {
            sf::Text instr("Arrows/WASD: mover  X: picar  C: colocar  1-5: seleccionar  Esc: salir", font, 14);
            instr.setFillColor(sf::Color::White);
            instr.setPosition(10, H*TILE + 4);
            window.draw(instr);
        }

        window.display();
    }
    return 0;
}
