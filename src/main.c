// Guide de survie - NumWorks (app externe .nwa)
// A placer dans src/main.c, avec survie_data.h dans le meme dossier src/

#include "eadk.h"
#include "survie_data.h"
#include <stdbool.h>

const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "Guide";
const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

#define RGB(r,g,b) ((eadk_color_t)((((r)&0xF8)<<8)|(((g)&0xFC)<<3)|((b)>>3)))
#define WHITE   RGB(255,255,255)
#define BLACK   RGB(0,0,0)
#define GRAY    RGB(110,110,110)
#define DARK    RGB(12,16,30)
#define TAB     RGB(60,60,75)
#define SELECT  RGB(40,60,110)
#define RED     RGB(220,40,40)
#define YELLOW  RGB(255,230,60)
#define LIME    RGB(120,230,120)

/* ---------- Affichage ---------- */

static void fill(int x, int y, int w, int h, eadk_color_t c) {
  eadk_rect_t r = {x, y, w, h};
  eadk_display_push_rect_uniform(r, c);
}

static void text(const char *s, int x, int y, bool big, eadk_color_t c, eadk_color_t bg) {
  eadk_point_t p = {x, y};
  eadk_display_draw_string(s, p, big, c, bg);
}

static int para(const char *s, int x, int y, int max, eadk_color_t c, eadk_color_t bg) {
  char line[48];
  int n = 0;
  while (*s) {
    int w = 0;
    while (s[w] && s[w] != ' ') w++;
    if (n > 0 && n + 1 + w > max) {
      line[n] = 0;
      text(line, x, y, false, c, bg);
      y += 16;
      n = 0;
    }
    if (n > 0) line[n++] = ' ';
    for (int i = 0; i < w && n < 46; i++) line[n++] = s[i];
    s += w;
    while (*s == ' ') s++;
  }
  if (n) {
    line[n] = 0;
    text(line, x, y, false, c, bg);
    y += 16;
  }
  return y;
}

/* ---------- Clavier ---------- */

// 0-9 : chiffres, 10 : OK, 11 : retour/effacer, 12 haut, 13 bas, 14 gauche, 15 droite
static int get_key(void) {
  while (eadk_keyboard_scan()) eadk_timing_msleep(20);
  while (1) {
    eadk_keyboard_state_t k = eadk_keyboard_scan();
#define K(x) eadk_keyboard_key_down(k, eadk_key_##x)
    if (K(zero)) return 0;
    if (K(one)) return 1;
    if (K(two)) return 2;
    if (K(three)) return 3;
    if (K(four)) return 4;
    if (K(five)) return 5;
    if (K(six)) return 6;
    if (K(seven)) return 7;
    if (K(eight)) return 8;
    if (K(nine)) return 9;
    if (K(ok) || K(exe)) return 10;
    if (K(back) || K(backspace)) return 11;
    if (K(up)) return 12;
    if (K(down)) return 13;
    if (K(left)) return 14;
    if (K(right)) return 15;
#undef K
    eadk_timing_msleep(20);
  }
}

/* ---------- Icones ---------- */

static eadk_color_t pal(char ch) {
  switch (ch) {
    case 'G': return RGB(60, 170, 60);
    case 'g': return RGB(30, 110, 40);
    case 'b': return RGB(130, 85, 40);
    case 'B': return RGB(90, 55, 30);
    case 't': return RGB(210, 180, 110);
    case 'p': return RGB(110, 40, 120);
    case 'w': return RGB(230, 230, 230);
    case 'y': return RGB(255, 220, 50);
  }
  return DARK;
}

static void draw_icone(int id, int ox, int oy, int sc) {
  fill(ox - 2, oy - 2, 16 * sc + 4, 16 * sc + 4, GRAY);
  fill(ox, oy, 16 * sc, 16 * sc, RGB(25, 35, 55));
  for (int r = 0; r < 16; r++) {
    for (int q = 0; q < 16; q++) {
      char ch = icone_pixels[id][r][q];
      if (ch != '.') fill(ox + q * sc, oy + r * sc, sc, sc, pal(ch));
    }
  }
}

/* ---------- Ecrans ---------- */

static void draw_dept(int len, int val) {
  char b[4] = "__";
  if (len == 1) {
    b[0] = '0' + val;
  } else if (len == 2) {
    b[0] = '0' + val / 10;
    b[1] = '0' + val % 10;
  }
  b[2] = 0;

  fill(0, 0, 320, 240, DARK);
  text("GUIDE DE SURVIE", 80, 16, true, YELLOW, DARK);
  text("Numero du departement :", 10, 70, false, WHITE, DARK);
  text(b, 135, 98, true, LIME, DARK);
  if (len == 2) {
    if (val >= 1 && val <= 95) {
      text("Zone :", 10, 150, false, WHITE, DARK);
      text(zone_noms[dept_zone[val]], 70, 150, false, YELLOW, DARK);
    } else {
      text("Numero invalide (01 a 95)", 10, 150, false, RED, DARK);
    }
  }
  text("Ex : 05 ou 29. Corse = 20", 10, 185, false, GRAY, DARK);
  text("[OK] valider    [Retour] effacer", 20, 214, false, GRAY, DARK);
}

static void draw_menu(int dept, int sel) {
  char h[] = "Departement XX";
  h[12] = '0' + dept / 10;
  h[13] = '0' + dept % 10;
  fill(0, 0, 320, 240, DARK);
  text(h, 10, 8, false, YELLOW, DARK);
  text(zone_noms[dept_zone[dept]], 10, 26, false, WHITE, DARK);
  for (int i = 0; i < 6; i++) {
    int y = 56 + i * 26;
    eadk_color_t bg = (i == sel) ? SELECT : DARK;
    fill(8, y - 3, 304, 22, bg);
    text(i < 5 ? habitat_noms[i] : "Regles de base", 16, y, false,
         (i == sel) ? YELLOW : WHITE, bg);
  }
  text("Haut/Bas choisir  [OK] ouvrir", 30, 218, false, GRAY, DARK);
}

static void draw_fiche(int dept, int hab, int sec, int psel) {
  const Fiche *f = survie_fiche(dept, (Habitat)hab);
  char d[] = "Dept XX";
  d[5] = '0' + dept / 10;
  d[6] = '0' + dept % 10;

  fill(0, 0, 320, 240, DARK);
  text(habitat_noms[hab], 10, 8, true, YELLOW, DARK);
  text(d, 250, 12, false, GRAY, DARK);
  if (hab != HAB_MONTAGNE) text(zone_noms[dept_zone[dept]], 10, 34, false, WHITE, DARK);

  if (f == NULL) {
    para("Fiche indisponible.", 10, 80, 40, WHITE, DARK);
  } else if (f->corde[0] == '-' && f->corde[1] == 0) {
    para(f->astuce, 10, 80, 40, WHITE, DARK);
  } else {
    const char *tabs[4] = {"Corde", "Manger", "Eau", "Astuce"};
    const char *body[4] = {f->corde, f->manger, f->eau, f->astuce};
    for (int t = 0; t < 4; t++) {
      int x = 6 + t * 78;
      eadk_color_t bg = (t == sec) ? YELLOW : TAB;
      fill(x, 54, 74, 20, bg);
      text(tabs[t], x + 8, 58, false, (t == sec) ? BLACK : WHITE, bg);
    }
    const ListePlantes *lp = (sec == 0) ? survie_cordes(dept, (Habitat)hab) : NULL;
    if (lp) {
      for (int i = 0; i < lp->n; i++) {
        int y = 82 + i * 20;
        eadk_color_t bg = (i == psel) ? SELECT : DARK;
        fill(8, y - 2, 196, 18, bg);
        text(lp->p[i]->nom, 14, y, false, (i == psel) ? YELLOW : WHITE, bg);
      }
      draw_icone(lp->p[psel]->icone, 220, 80, 5);
      para(lp->p[psel]->methode, 10, 168, 40, WHITE, DARK);
    } else {
      para(body[sec], 10, 88, 40, WHITE, DARK);
    }
  }
  if (sec == 0 && survie_cordes(dept, (Habitat)hab))
    text("Haut/Bas plante  Gauche/Droite onglet", 8, 224, false, GRAY, DARK);
  else
    text("Gauche/Droite onglet  [Retour] menu", 8, 224, false, GRAY, DARK);
}

static void draw_regle(int r) {
  char n[] = "Regle X/6";
  n[6] = '1' + r;
  fill(0, 0, 320, 240, DARK);
  text("REGLES DE BASE", 80, 12, true, YELLOW, DARK);
  text(n, 10, 50, false, LIME, DARK);
  para(survie_regles[r], 10, 80, 40, WHITE, DARK);
  text("Gauche/Droite changer  [Retour] menu", 8, 218, false, GRAY, DARK);
}

/* ---------- Programme ---------- */

int main(int argc, char *argv[]) {
  int screen = 0;  // 0 departement, 1 menu, 2 fiche, 3 regles
  int len = 0, val = 0;
  int dept = 0, sel = 0, hab = 0, sec = 0, ridx = 0, psel = 0;

  while (1) {
    if (screen == 0) draw_dept(len, val);
    else if (screen == 1) draw_menu(dept, sel);
    else if (screen == 2) draw_fiche(dept, hab, sec, psel);
    else draw_regle(ridx);

    int k = get_key();

    if (screen == 0) {
      if (k <= 9 && len < 2) {
        val = val * 10 + k;
        len++;
      } else if (k == 11 && len > 0) {
        val /= 10;
        len--;
      } else if (k == 10 && len == 2 && val >= 1 && val <= 95) {
        dept = val;
        sel = 0;
        screen = 1;
      }
    } else if (screen == 1) {
      if (k == 12) sel = (sel + 5) % 6;
      else if (k == 13) sel = (sel + 1) % 6;
      else if (k == 10) {
        if (sel == 5) {
          ridx = 0;
          screen = 3;
        } else {
          hab = sel;
          sec = 0;
          psel = 0;
          screen = 2;
        }
      } else if (k == 11) {
        screen = 0;
      }
    } else if (screen == 2) {
      const ListePlantes *lp = (sec == 0) ? survie_cordes(dept, (Habitat)hab) : NULL;
      if (k == 12 && lp) psel = (psel + lp->n - 1) % lp->n;
      else if (k == 13 && lp) psel = (psel + 1) % lp->n;
      else if (k == 14) { sec = (sec + 3) % 4; psel = 0; }
      else if (k == 15 || k == 10) { sec = (sec + 1) % 4; psel = 0; }
      else if (k == 11) screen = 1;
    } else {
      if (k == 14) ridx = (ridx + NB_REGLES - 1) % NB_REGLES;
      else if (k == 15 || k == 10) ridx = (ridx + 1) % NB_REGLES;
      else if (k == 11) screen = 1;
    }
  }
  return 0;
}
