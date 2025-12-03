#include <bits/stdc++.h>
using namespace std;

// Juego 2D muy simple tipo "Minecraft" en consola
// Controles (teclear + Enter):
// a = izquierda, d = derecha, w = arriba, s = abajo
// x = picar (remove block in facing direction)
// c = construir (place selected block in facing direction)
// 1-5 = seleccionar tipo de bloque
// h = ayuda, q = salir

const int W = 20;
const int H = 12;

enum Block { AIR=' ', GRASS='G', DIRT='D', STONE='S', WOOD='W', BEDR='B' };

struct Player {
    int x, y;
    int fx, fy; // facing
    char selected;
    map<char,int> inv;
};

vector<string> world;

void init_world() {
    world.assign(H, string(W, (char)AIR));
    // cielo (filas 0-5) aire
    // generar terreno simple: capa de grass en y=7, dirt debajo, stone debajo
    int ground = H-4;
    for (int y=ground; y<H-1; ++y) {
        for (int x=0; x<W; ++x) {
            if (y==ground) world[y][x] = (char)GRASS;
            else if (y< H-2) world[y][x] = (char)DIRT;
            else world[y][x] = (char)STONE;
        }
    }
    // bedrock bottom row
    for (int x=0; x<W; ++x) world[H-1][x] = (char)BEDR;

    // simple árbol
    int tx = 4, ty = ground-1;
    world[ty][tx] = (char)WOOD;
    world[ty-1][tx] = (char)WOOD;
    world[ty-2][tx] = (char)WOOD;
}

void render(const Player &p) {
    system("cls");
    for (int y=0; y<H; ++y) {
        for (int x=0; x<W; ++x) {
            if (x==p.x && y==p.y) cout << 'P';
            else cout << world[y][x];
        }
        cout << '\n';
    }
    cout << "Inventario: ";
    cout << "(1)G=" << p.inv.at((char)GRASS) << " ";
    cout << "(2)D=" << p.inv.at((char)DIRT) << " ";
    cout << "(3)S=" << p.inv.at((char)STONE) << " ";
    cout << "(4)W=" << p.inv.at((char)WOOD) << " ";
    cout << "(5)B=" << p.inv.at((char)BEDR) << " ";
    cout << "  Seleccionado: " << p.selected << "\n";
    cout << "Comandos: a/d/w/s mover, x picar, c construir, 1-5 seleccionar, h ayuda, q salir\n";
}

bool in_bounds(int x,int y){ return x>=0 && x<W && y>=0 && y<H; }

char block_at(int x,int y){ if(!in_bounds(x,y)) return (char)BEDR; return world[y][x]; }

void set_block(int x,int y,char b){ if(in_bounds(x,y)) world[y][x]=b; }

void dig(Player &p) {
    int tx = p.x + p.fx;
    int ty = p.y + p.fy;
    if (!in_bounds(tx,ty)) return;
    char b = block_at(tx,ty);
    if (b==(char)AIR || b==(char)BEDR) return;
    // recoger
    p.inv[b]++;
    set_block(tx,ty,(char)AIR);
}

void place(Player &p) {
    int tx = p.x + p.fx;
    int ty = p.y + p.fy;
    if (!in_bounds(tx,ty)) return;
    if (block_at(tx,ty)!=(char)AIR) return;
    char b = p.selected;
    if (p.inv[b] <= 0) return;
    p.inv[b]--;
    set_block(tx,ty,b);
}

int main(){
    init_world();
    Player p;
    p.x = W/2; p.y = H-5; p.fx = 1; p.fy = 0; p.selected = (char)GRASS;
    p.inv[(char)GRASS]=5;
    p.inv[(char)DIRT]=5;
    p.inv[(char)STONE]=3;
    p.inv[(char)WOOD]=2;
    p.inv[(char)BEDR]=0;

    string cmd;
    render(p);
    while (true){
        cout << "> ";
        if(!getline(cin, cmd)) break;
        if (cmd.empty()) continue;
        char c = cmd[0];
        if (c=='q') break;
        if (c=='h') {
            cout << "Ayuda:\n";
            cout << "a/d/w/s mover, x picar, c construir, 1:G 2:D 3:S 4:W 5:B, q salir\n";
            cout << "Pulsa Enter para continuar...\n";
            getline(cin, cmd);
            render(p);
            continue;
        }
        if (c=='a') { if (p.x>0) p.x--; p.fx=-1; p.fy=0; }
        else if (c=='d') { if (p.x<W-1) p.x++; p.fx=1; p.fy=0; }
        else if (c=='w') { if (p.y>0) p.y--; p.fx=0; p.fy=-1; }
        else if (c=='s') { if (p.y<H-1) p.y++; p.fx=0; p.fy=1; }
        else if (c=='x') dig(p);
        else if (c=='c') place(p);
        else if (c>='1' && c<='5'){
            int idx = c - '1';
            char mapSel[5] = {(char)GRASS,(char)DIRT,(char)STONE,(char)WOOD,(char)BEDR};
            p.selected = mapSel[idx];
        }
        render(p);
    }

    cout << "Saliendo...\n";
    return 0;
}
