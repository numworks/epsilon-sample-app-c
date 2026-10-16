// Bibliotheque de survie - France metropolitaine
// Principe : numero de departement -> zone climatique -> fiche selon le milieu.
// Les plantes ne suivent pas les limites administratives : les zones sont
// des approximations. Textes en ASCII (pas d'accents) pour la police NumWorks.
//
// Utilisation :
//   const Fiche *f = survie_fiche(29, HAB_FORET);   // 29 = Finistere
//   f->corde, f->manger, f->eau, f->astuce
//
// Corse : utiliser le numero 20. Departements 01 a 95.

#ifndef SURVIE_DATA_H
#define SURVIE_DATA_H

#include <stdint.h>
#include <stddef.h>

typedef enum {
  ZONE_OCEANIQUE = 0,
  ZONE_CONTINENTAL = 1,
  ZONE_MEDITERRANEEN = 2
} Zone;

typedef enum {
  HAB_FORET = 0,
  HAB_LITTORAL,
  HAB_PLAINE,
  HAB_EAU_DOUCE,
  HAB_MONTAGNE,
  HAB_COUNT
} Habitat;

typedef struct {
  const char *corde;
  const char *manger;
  const char *eau;
  const char *astuce;
} Fiche;

// Icones disponibles (dessins pixel art 16x16 plus bas dans ce fichier)
typedef enum {
  ICO_TILLEUL = 0, ICO_ORTIE, ICO_RONCE, ICO_OSIER,
  ICO_JONC, ICO_GENET, ICO_RACINE, ICO_CORDE, ICO_COUNT
} Icone;

typedef struct {
  const char *nom;
  uint8_t icone;
  const char *methode;
} Plante;

typedef struct {
  const Plante *const *p;
  uint8_t n;
} ListePlantes;

static const char *const zone_noms[3] = {
  "Oceanique", "Continental", "Mediterraneen"
};

static const char *const habitat_noms[HAB_COUNT] = {
  "Foret", "Mer / plage", "Plaine / haies", "Riviere / lac", "Montagne"
};

// Index = numero de departement (0 inutilise). 0 = oceanique,
// 1 = continental, 2 = mediterraneen. Les zones de montagne sont gerees
// par le milieu HAB_MONTAGNE, pas par la zone.
static const uint8_t dept_zone[96] = {
  1, 1,1,1,2,1,2,2,1,1,   // 00-09
  1,2,1,2,0,1,0,0,1,1,    // 10-19
  2,1,0,1,0,1,2,0,1,0,    // 20-29 (20 = Corse)
  2,1,1,0,2,0,1,1,1,1,    // 30-39
  0,1,1,1,0,1,1,1,1,0,    // 40-49
  0,1,1,0,1,1,0,1,1,0,    // 50-59
  1,0,0,1,0,1,2,1,1,1,    // 60-69
  1,1,0,1,1,1,0,1,1,0,    // 70-79
  0,1,1,2,2,0,0,1,1,1,    // 80-89
  1,1,1,1,1,1             // 90-95
};

static const Fiche fiche_pas_de_mer = {
  "-", "-", "-", "Pas de littoral dans cette zone : voir Riviere / lac."
};

// ---------- Zone oceanique (Bretagne, Normandie, Nord, Atlantique) ----------
static const Fiche fiches_oceanique[4] = {
  // Foret
  { "Liber de tilleul, tiges d'ortie seches, ronces effeuillees, osier fin.",
    "Chataignes et noisettes cuites, glands (a lessiver), mures, ortie cuite.",
    "Ruisseaux : filtrer au tissu puis bouillir. Rosee recoltee au tissu.",
    "Abri de branches adosse a un arbre, sol isole par des feuilles seches." },
  // Mer / plage
  { "Peu de cordage sur la plage : cordes et filets echoues, ortie et ronces en haut de plage.",
    "Laitue de mer, dulse, nori (rincer). Coquillages : risque de toxines, seulement en dernier recours et cuits.",
    "Eau de mer NON potable. Chercher ruisseau ou source en arriere du littoral : filtrer + bouillir.",
    "Surveiller les marees, rester au-dessus de la laisse de haute mer. Bois flotte sec pour le feu." },
  // Plaine / haies
  { "Ortie (fibres des tiges), ronces, osier des haies, lierre pour liens courts.",
    "Pissenlit, plantain, ortie cuite, mures, noisettes. Eviter les bords de champs traites.",
    "Mares et fosses douteux : filtrer + bouillir. Pluie recuperee sur une bache.",
    "Les haies coupent le vent. Ne jamais manger d'ombelles : la cigue ressemble a la carotte." },
  // Riviere / lac
  { "Joncs et roseaux tresses, saule et osier des berges.",
    "Poissons a la ligne, racines de typha cuites. Cresson sauvage seulement bien cuit.",
    "Eau courante et claire plutot que stagnante : filtrer + bouillir 1 min (3 min en altitude).",
    "Dormir loin du bord (crues, moustiques). Suivre le cours d'eau mene souvent a un village." }
};

// ---------- Zone continentale (centre, est, region parisienne, sud-ouest) ----------
static const Fiche fiches_continental[4] = {
  // Foret
  { "Liber de tilleul, tiges d'ortie, racines fines d'epicea, saule.",
    "Noisettes, chataignes cuites, mures, framboises, myrtilles. Pissenlit et plantain en lisiere.",
    "Sources et ruisseaux : filtrer + bouillir. En hiver, fondre la neige (ne pas la manger).",
    "Abri en appentis (branches inclinees). Bois mort encore sur l'arbre = plus sec." },
  // Mer / plage (inexistant)
  { "-", "-", "-", "Pas de littoral dans cette zone : voir Riviere / lac." },
  // Plaine / haies
  { "Ortie, ronces, saule des haies.",
    "Pissenlit, plantain, ortie cuite, mures, noix et noisettes.",
    "Fosses et mares : filtrer + bouillir. Rosee et pluie avec un tissu ou une bache.",
    "Rester pres des chemins et se rendre visible : grands signaux au sol, miroir, feu fumeux." },
  // Riviere / lac
  { "Joncs, roseaux, saule des berges.",
    "Poissons a la ligne, racines de typha cuites, mures sur les berges.",
    "Eau courante claire : filtrer + bouillir 1 min (3 min en altitude).",
    "Camper un peu en hauteur (crues). Suivre l'aval d'une riviere mene souvent a des habitations." }
};

// ---------- Zone mediterraneenne (Provence, Languedoc, Corse) ----------
static const Fiche fiches_mediterraneen[4] = {
  // Foret / maquis
  { "Genet d'Espagne (tiges souples), ronces, racines fines de pin.",
    "Glands de chene vert (a lessiver), arbouses, figues, mures, pignons de pin parasol.",
    "Rare l'ete : lits de ruisseaux a sec (creuser), rosee, pluie. Filtrer + bouillir.",
    "Se reposer a l'ombre aux heures chaudes, marcher tot ou tard. Pas de feu en ete : risque d'incendie." },
  // Mer / plage
  { "Joncs et roseaux pres des etangs, genet d'Espagne en arriere-plage.",
    "Figues de Barbarie (retirer les epines fines en les roulant dans le sable), algues rincees. Coquillages : risque.",
    "Eau de mer NON potable. Peu de sources : fonds de vallons, puits, fontaines. Filtrer + bouillir.",
    "Soleil fort : couvrir tete et peau, faire de l'ombre avec une bache. Vent fort possible (mistral)." },
  // Plaine / garrigue
  { "Genet d'Espagne, ronces.",
    "Figues, mures. Romarin et thym en infusion (aromates, pas un repas).",
    "Rosee, pluie sur bache, lits de ruisseaux a sec. Filtrer + bouillir.",
    "Eviter de marcher en plein soleil (10h-17h). Reperer les points hauts pour s'orienter." },
  // Riviere / lac
  { "Roseaux et joncs, saule des berges.",
    "Poissons a la ligne, racines de typha cuites, mures le long des berges.",
    "Eau courante claire : filtrer + bouillir. Mefiance avec les eaux stagnantes l'ete.",
    "L'eau est un repere : rester proche et visible. Ombre indispensable en journee." }
};

// ---------- Montagne (toutes zones : Alpes, Pyrenees, Jura, Vosges, Massif central) ----------
static const Fiche fiche_montagne = {
  "Racines fines d'epicea ou de pin, liber de tilleul en bas de vallee, genets.",
  "Myrtilles, framboises sauvages, noisettes, pissenlit. Peu de nourriture : economiser son energie.",
  "Neige et glace : les FONDRE avant de boire. Ruisseaux : filtrer + bouillir 3 min.",
  "Hypothermie = danger n.1 : abri du vent, rester sec. Descendre par les vallees, pas de nuit." };

// ---------- Regles generales ----------
#define NB_REGLES 6
static const char *const survie_regles[NB_REGLES] = {
  "Priorites : securite et abri, eau, signal et feu, puis nourriture.",
  "Regle des 3 : 3 h sans abri par grand froid, 3 jours sans eau, 3 semaines sans manger.",
  "Ne jamais manger : champignons, baies inconnues, ombelles (cigue), if.",
  "Toujours filtrer puis bouillir l'eau de surface (1 min, 3 min en altitude).",
  "Rester pres de l'epave ou d'un point visible : on retrouve plus facilement.",
  "Ces fiches sont un jeu : en vrai, ne mange que ce que tu identifies a coup sur."
};

// ---------- Icones pixel art 16x16 ----------
// Lettres : G vert, g vert fonce, b brun, B brun fonce, t beige, p violet,
// w blanc, y jaune, '.' = transparent
static const char *const icone_pixels[ICO_COUNT][16] = {
  // ICO_TILLEUL
  { "................", "..GGG......GGG..", ".GGGGG....GGGGG.", "GGGGGGG..GGGGGGG",
    "GGGGGGGggGGGGGGG", "GGGGGGGggGGGGGGG", ".GGGGGGggGGGGGG.", ".GGGGGGggGGGGGG.",
    "..GGGGGGGGGGGG..", "...GGGGGGGGGG...", "....GGGGGGGG....", ".....GGGGGG.....",
    "......GGGG......", ".......GG.......", ".......bb.......", ".......bb......." },
  // ICO_ORTIE
  { ".......GG.......", "......GGGG......", ".....GgGGgG.....", "......GGGG......",
    "..GG.gGGGGg.GG..", ".GGGGgGGGGgGGGG.", "..GGGGgGGgGGGG..", "...GGGGGGGGGG...",
    "....GGgGGgGG....", ".....GGGGGG.....", "......gGGg......", ".......gg.......",
    ".......gg.......", ".......bb.......", ".......bb.......", ".......bb......." },
  // ICO_RONCE
  { "................", ".........GG.....", "........GGGG....", ".....pp..GG.....",
    "....pppp..B.....", "....pppp.B......", ".....pp.B.w.....", "....G...B.......",
    "...GGG.wB.......", "....G..B........", "......wB........", ".....B.B.w......",
    ".....B..B.......", "....wB...B......", "....B....B......", "................" },
  // ICO_OSIER
  { "..G..G..G..G....", "..t..t..t..t....", "..t..t..t..t....", "..t..t..t..t....",
    "..t..t..t..t....", ".BBBBBBBBBBBB...", "..t..t..t..t....", "..t..t..t..t....",
    "..t..t..t..t....", "..t..t..t..t....", "..t..t..t..t....", "..t..t..t..t....",
    "..t..t..t..t....", ".BBBBBBBBBBBB...", "..t..t..t..t....", "..t..t..t..t...." },
  // ICO_JONC
  { ".......B........", "......BBB.......", "......BBB.......", "......BBB.......",
    "......BBB.......", ".......G.....G..", ".......G....G...", "..G....G....G...",
    "..G....G...G....", "...G...G...G....", "...G...G..G.....", "....G..G..G.....",
    "....G..G.G......", ".....G.G.G......", ".....GGG........", "......G........." },
  // ICO_GENET
  { "..y.....y....y..", ".yyy...yyy..yyy.", "..y..G..y.G..y..", "...G.G...G.G....",
    "...G..G..G.G....", "....G.G.G..G....", "....G.G.G.G.....", ".....GGGG.G.....",
    ".....GGGGG......", "......GGG.......", "......GGG.......", ".......G........",
    ".......G........", ".......G........", ".......b........", ".......b........" },
  // ICO_RACINE
  { "................", ".tt.............", "..ttt...........", "....ttt.........",
    "......ttt.....tt", "........ttt.ttt.", ".........tttt...", "..........tt....",
    ".....tt..ttt....", "....ttt.tt......", "...tt.ttt.......", "..tt.tt.........",
    "..t.tt..........", "...tt...........", "..tt............", ".tt............." },
  // ICO_CORDE
  { "................", "....tttttttt....", "...tBtBtBtBtt...", "..tBt......tBt..",
    ".tBt..tttt..tBt.", ".tBt.tBttBt.tBt.", ".tBt.tt..tt.tBt.", ".tBt.tBttBt.tBt.",
    ".tBt..tttt..tBt.", "..tBt......tBt..", "...tBtBtBtBtt...", "....tttttttt....",
    "......tt........", ".......tt.......", "........tt......", "................" }
};

// ---------- Plantes pour la corde ----------
static const Plante P_TILLEUL = {"Tilleul", ICO_TILLEUL,
  "Prendre le liber (ecorce interieure), le faire tremper, puis le tresser en cordelette."};
static const Plante P_ORTIE = {"Ortie", ICO_ORTIE,
  "Tiges seches : ecraser, separer les fibres, les rouler et les tordre en cordelette."};
static const Plante P_RONCE = {"Ronce", ICO_RONCE,
  "Effeuiller et retirer les epines (avec des gants !), puis tresser les brins."};
static const Plante P_OSIER = {"Osier / saule", ICO_OSIER,
  "Tiges souples : les tordre pour faire des liens solides et flexibles."};
static const Plante P_JONC = {"Jonc / roseau", ICO_JONC,
  "Tresser plusieurs tiges ensemble pour allonger et renforcer la corde."};
static const Plante P_GENET = {"Genet d'Espagne", ICO_GENET,
  "Tiges souples : les tordre ou les tresser pour faire des liens."};
static const Plante P_EPICEA = {"Racines d'epicea", ICO_RACINE,
  "Racines fines et souples : les deterrer, les fendre en deux, puis les tresser en lien solide."};
static const Plante P_PIN = {"Racines de pin", ICO_RACINE,
  "Racines fines et souples : les deterrer, les fendre en deux, puis les tresser en lien solide."};
static const Plante P_ECHOUE = {"Cordes echouees", ICO_CORDE,
  "Filets et cordes rejetes par la mer : les rincer, puis les defaire pour recuperer le fil."};

static const Plante *const L_O_FORET[] = {&P_TILLEUL, &P_ORTIE, &P_RONCE, &P_OSIER};
static const Plante *const L_O_LITTORAL[] = {&P_ECHOUE, &P_ORTIE, &P_RONCE};
static const Plante *const L_O_PLAINE[] = {&P_ORTIE, &P_RONCE, &P_OSIER};
static const Plante *const L_EAU[] = {&P_JONC, &P_OSIER};
static const Plante *const L_C_FORET[] = {&P_TILLEUL, &P_ORTIE, &P_EPICEA, &P_OSIER};
static const Plante *const L_C_PLAINE[] = {&P_ORTIE, &P_RONCE, &P_OSIER};
static const Plante *const L_M_FORET[] = {&P_GENET, &P_RONCE, &P_PIN};
static const Plante *const L_M_LITTORAL[] = {&P_JONC, &P_GENET};
static const Plante *const L_M_PLAINE[] = {&P_GENET, &P_RONCE};
static const Plante *const L_MONTAGNE[] = {&P_EPICEA, &P_TILLEUL, &P_GENET};

#define LISTE(a) { a, (uint8_t)(sizeof(a) / sizeof((a)[0])) }

// [zone][habitat : foret, littoral, plaine, eau douce]
static const ListePlantes cordes[3][4] = {
  { LISTE(L_O_FORET), LISTE(L_O_LITTORAL), LISTE(L_O_PLAINE), LISTE(L_EAU) },
  { LISTE(L_C_FORET), {NULL, 0},           LISTE(L_C_PLAINE), LISTE(L_EAU) },
  { LISTE(L_M_FORET), LISTE(L_M_LITTORAL), LISTE(L_M_PLAINE), LISTE(L_EAU) }
};
static const ListePlantes cordes_montagne = LISTE(L_MONTAGNE);

// Retourne la liste des plantes pour la corde, ou NULL s'il n'y en a pas
static const ListePlantes *survie_cordes(int dept, Habitat h) {
  if (h == HAB_MONTAGNE) return &cordes_montagne;
  if (dept < 1 || dept > 95 || h < 0 || h > HAB_EAU_DOUCE) return NULL;
  const ListePlantes *l = &cordes[dept_zone[dept]][h];
  return l->n ? l : NULL;
}

// ---------- Acces ----------
static const Fiche *survie_fiche(int dept, Habitat h) {
  if (h == HAB_MONTAGNE) return &fiche_montagne;
  if (dept < 1 || dept > 95 || h < 0 || h > HAB_EAU_DOUCE) return NULL;
  switch (dept_zone[dept]) {
    case ZONE_OCEANIQUE:     return &fiches_oceanique[h];
    case ZONE_CONTINENTAL:   return &fiches_continental[h];
    default:                 return &fiches_mediterraneen[h];
  }
}

#endif
