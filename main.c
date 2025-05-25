    #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <curl/curl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define MAX_dosya_uzunluk_LENGTH 256

    typedef struct {
        int saldiri;
        int savunma;
        int saglik;
        float kritik_sans;
    } karkater_degiskenler;
    typedef struct {
        char bonus_turu[MAX_dosya_uzunluk_LENGTH];
        char aciklamakahr[MAX_dosya_uzunluk_LENGTH];
        char bonus_degeri[MAX_dosya_uzunluk_LENGTH];
    } komutan_ozellik;
    typedef struct {
        char etki_degeri[MAX_dosya_uzunluk_LENGTH];
        char aciklamacanv[MAX_dosya_uzunluk_LENGTH]; 
        char etki_turu[MAX_dosya_uzunluk_LENGTH];
    }canavar_ozellik;
    typedef struct {
        char deger[MAX_dosya_uzunluk_LENGTH];
    }arastirma;
    typedef struct
    {
    int piyadesayisi;
    int okcusayisi;
    int suvarisayisi;
    int kusatmacisayisi;
    int orkdovuscusayisi;
    int mizrakcisayisi;
    int vargsayisi;
    int trolsayisi;

    }senaryoverisi;
    struct InsanVeri {
    int savunma_ustaligi;
    int saldiri_gelistirmesi;
    int elit_egitim;
    int kusatma_ustaligi;
    char insankahr[MAX_dosya_uzunluk_LENGTH];
    char insancnvr[MAX_dosya_uzunluk_LENGTH];
};
    struct OrkVeri {
    int savunma_ustaligi;
    int saldiri_gelistirmesi;
    int elit_egitim;
    int kusatma_ustaligi;
     char orkkahr[MAX_dosya_uzunluk_LENGTH];
    char orkcnvr[MAX_dosya_uzunluk_LENGTH];
};
    typedef struct 
    {
        senaryoverisi insanbirimler;
        // senaryoverisi insanbirimler;
    }insan_sayi;
    typedef struct 
    {
        senaryoverisi orkbirimler;
        // senaryoverisi orkbirimler;
    }ork_sayi;
    typedef struct {
        karkater_degiskenler piyadeler;
        karkater_degiskenler okcular;
        karkater_degiskenler suvariler;
        karkater_degiskenler kusatma_makineleri;
    }insan_imp;
    typedef struct{
        komutan_ozellik Alparslan;
        komutan_ozellik Fatih_Sultan_Mehmet;
        komutan_ozellik Yavuz_Sultan_Selim;
        komutan_ozellik Mete_Han;
        komutan_ozellik Tugrul_Bey;
    } insan_kahr;
    typedef struct {
        karkater_degiskenler ork_dovusculeri;
        karkater_degiskenler mizrakcilar;
        karkater_degiskenler varg_binicileri;
        karkater_degiskenler troller;
    } ork_legion;
    typedef struct{
    komutan_ozellik Goruk_Vahsi;
        komutan_ozellik Thruk_Kemikkiran;
        komutan_ozellik Vrog_Kafakiran;
        komutan_ozellik Ugar_Zalim;
     
    } ork_kahr;
    typedef struct {
        canavar_ozellik Ejderha;
        canavar_ozellik Agri_Dagi_Devleri;
        canavar_ozellik Tepegoz;
        canavar_ozellik Karakurt;
        canavar_ozellik Samur;
    }insan_canavar;
    typedef struct {
        canavar_ozellik Kara_Troll;
        canavar_ozellik Golge_Kurtlari;
        canavar_ozellik Camur_Devleri;
        canavar_ozellik Ates_Iblisi;
        canavar_ozellik Buz_Devleri;
    }ork_canavar;
    typedef struct{
    arastirma seviye_1;
    arastirma seviye_2;
    arastirma seviye_3;
    }savunma_ustasi, saldiri_gelistirmesi, elit_egitim, kusatma_ustaligi;

    void degiskenAyir(FILE *file, karkater_degiskenler *karkater_degiskenler) {
    char dosya_uzunluk[MAX_dosya_uzunluk_LENGTH];
    int alindi[4] = {0, 0, 0, 0}; 
    while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file)) {
        if (strstr(dosya_uzunluk, "saldiri")) {
            sscanf(dosya_uzunluk, " \"saldiri\": %d,", &karkater_degiskenler->saldiri);
            alindi[0] = 1; // Saldırı alındı
        } else if (strstr(dosya_uzunluk, "savunma")) {
            sscanf(dosya_uzunluk, " \"savunma\": %d,", &karkater_degiskenler->savunma);
            alindi[1] = 1; // Savunma alındı
        } else if (strstr(dosya_uzunluk, "saglik")) {
            sscanf(dosya_uzunluk, " \"saglik\": %d,", &karkater_degiskenler->saglik);
            alindi[2] = 1; // Sağlık alındı
        } else if (strstr(dosya_uzunluk, "kritik_sans")) {
            sscanf(dosya_uzunluk, " \"kritik_sans\": %f", &karkater_degiskenler->kritik_sans);
            alindi[3] = 1; // Kritik şans alındı
        }
    
        if (alindi[0] && alindi[1] && alindi[2] && alindi[3]) {
            break;
        }}}
    void komutanAyir(FILE *file, komutan_ozellik *komutan_ozellik) {
        char dosya_uzunluk[MAX_dosya_uzunluk_LENGTH];
        while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file)) {
            if (strstr(dosya_uzunluk, "bonus_turu")) {
                sscanf(dosya_uzunluk, " \"bonus_turu\":  \"%[^\"]\"", komutan_ozellik->bonus_turu);
            } else if (strstr(dosya_uzunluk, "aciklama")) {
                sscanf(dosya_uzunluk, " \"aciklama\": \"%s", komutan_ozellik->aciklamakahr);
            } else if (strstr(dosya_uzunluk, "bonus_degeri")) {
                sscanf(dosya_uzunluk, " \"bonus_degeri\": \"%[^\"]\"", komutan_ozellik->bonus_degeri);
            }
            if (strlen(komutan_ozellik->bonus_turu) > 0 && 
                strlen(komutan_ozellik->aciklamakahr) > 0 && 
                strlen(komutan_ozellik->bonus_degeri) > 0
                ) {
                break;
                }}}
    void canavarAyir(FILE *file, canavar_ozellik *canavar_ozellik) {
        char dosya_uzunluk[MAX_dosya_uzunluk_LENGTH];

        while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file)) {
            if (strstr(dosya_uzunluk, "etki_degeri")) {
                sscanf(dosya_uzunluk, " \"etki_degeri\": \"%[^\"]\"", canavar_ozellik->etki_degeri);
            }else if (strstr(dosya_uzunluk, "aciklama")) {
                sscanf(dosya_uzunluk, " \"aciklama\": \"%s", canavar_ozellik->aciklamacanv);
            }  else if (strstr(dosya_uzunluk, "etki_turu")) {
                sscanf(dosya_uzunluk, " \"etki_turu\": \"%[^\"]\"", canavar_ozellik->etki_turu);
            } 
            if (strlen(canavar_ozellik->etki_degeri) > 0 && 
                strlen(canavar_ozellik->etki_turu) > 0 &&
                strlen(canavar_ozellik->aciklamacanv) > 0 
                ) {
                break;
                }}}
    void researchAyir(FILE *file, arastirma *arastirma) {
        char dosya_uzunluk[MAX_dosya_uzunluk_LENGTH];

        while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file)) {
            if (strstr(dosya_uzunluk, "deger")) {
                sscanf(dosya_uzunluk, " \"deger\": \"%[^\"]\"", arastirma->deger);
            } 
            if (strlen(arastirma->deger) > 0 ) {
                break;
                }}}
    void senaryo1Ayir(FILE *file, senaryoverisi *senaryoverisi) {
        char dosya_uzunluk[MAX_dosya_uzunluk_LENGTH];

        while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file)) {
            if (strstr(dosya_uzunluk, "piyadeler")) {
                sscanf(dosya_uzunluk, " \"piyadeler\": %d,",&senaryoverisi->piyadesayisi);
            } else if (strstr(dosya_uzunluk, "okcular")) {
                sscanf(dosya_uzunluk, " \"okcular\": %d,", &senaryoverisi->okcusayisi);
            } else if (strstr(dosya_uzunluk, "suvariler")) {
                sscanf(dosya_uzunluk, " \"suvariler\": %d,", &senaryoverisi->suvarisayisi);
            } else if (strstr(dosya_uzunluk, "kusatma_makineleri")) {
                sscanf(dosya_uzunluk, " \"kusatma_makineleri\": %d,", &senaryoverisi->kusatmacisayisi);
            } else if (strstr(dosya_uzunluk, "ork_dovusculeri")) {
                sscanf(dosya_uzunluk, " \"ork_dovusculeri\": %d,", &senaryoverisi->orkdovuscusayisi);
            } else if (strstr(dosya_uzunluk, "mizrakcilar")) {
                sscanf(dosya_uzunluk, " \"mizrakcilar\": %d,", &senaryoverisi->mizrakcisayisi);
            } else if (strstr(dosya_uzunluk, "varg_binicileri")) {
                sscanf(dosya_uzunluk, " \"varg_binicileri\": %d,", &senaryoverisi->vargsayisi);
            } else if (strstr(dosya_uzunluk, "troller")) {
                sscanf(dosya_uzunluk, " \"troller\": %d,", &senaryoverisi->trolsayisi);
            }
            
            if (senaryoverisi->piyadesayisi > 0 && 
                senaryoverisi->okcusayisi > 0 && 
                senaryoverisi->suvarisayisi > 0 && 
                senaryoverisi->kusatmacisayisi > 0 && 
                senaryoverisi->orkdovuscusayisi > 0 && 
                senaryoverisi->mizrakcisayisi > 0 && 
                senaryoverisi->vargsayisi > 0 && 
                senaryoverisi->trolsayisi > 0
                ) {
                break;}}}
    void parse_insan(const char *json, struct InsanVeri *i_veri) {
    // Varsayılan değerler
    i_veri->savunma_ustaligi = 0;
    i_veri->saldiri_gelistirmesi = 0;
    i_veri->elit_egitim = 0;
    i_veri->kusatma_ustaligi = 0;

    // "insan_imparatorlugu" kısmını bul
    char *insan_start = strstr(json, "\"insan_imparatorlugu\":");
    if (insan_start) {
        char *arastirma_start = strstr(insan_start, "\"arastirma_seviyesi\":");
        if (arastirma_start) {
            // Araştırma seviyesinin sonunu bul
            char *insan_end = strstr(arastirma_start, "}");
            if (insan_end) {
                // Araştırma seviyesini ayrıştır
                char *current = arastirma_start;

                // Savunma ustalığı
                char *savunma_start = strstr(current, "\"savunma_ustaligi\":");
                if (savunma_start && savunma_start < insan_end) {
                    sscanf(savunma_start, "\"savunma_ustaligi\": %d", &i_veri->savunma_ustaligi);
                }
                // Saldırı gelişimi
                char *saldiri_start = strstr(current, "\"saldiri_gelistirmesi\":");
                if (saldiri_start && saldiri_start < insan_end) {
                    sscanf(saldiri_start, "\"saldiri_gelistirmesi\": %d", &i_veri->saldiri_gelistirmesi);
                }
                // Kuşatma ustalığı
                char *kusatma_start = strstr(current, "\"kusatma_ustaligi\":");
                if (kusatma_start && kusatma_start < insan_end) {
                    sscanf(kusatma_start, "\"kusatma_ustaligi\": %d", &i_veri->kusatma_ustaligi);
                }
                // Elit eğitim
                char *elit_start = strstr(current, "\"elit_egitim\":");
                if (elit_start && elit_start < insan_end) {
                    sscanf(elit_start, "\"elit_egitim\": %d", &i_veri->elit_egitim);
                }}}}}
    void parse_ork(const char *json, struct OrkVeri *o_veri) {
    // Varsayılan değerler
    o_veri->savunma_ustaligi = 0;
    o_veri->saldiri_gelistirmesi = 0;
    o_veri->elit_egitim = 0;
    o_veri->kusatma_ustaligi = 0;

    // "ork_legi" kısmını bul
    char *ork_start = strstr(json, "\"ork_legi\":");
    if (ork_start) {
        char *arastirma_start = strstr(ork_start, "\"arastirma_seviyesi\":");
        if (arastirma_start) {
            // Araştırma seviyesinin sonunu bul
            char *ork_end = strstr(arastirma_start, "}");
            if (ork_end) {
                // Araştırma seviyesini ayrıştır
                char *current = arastirma_start;
                // Saldırı gelişimi
                char *saldiri_start = strstr(current, "\"saldiri_gelistirmesi\":");
                if (saldiri_start && saldiri_start < ork_end) {
                    sscanf(saldiri_start, "\"saldiri_gelistirmesi\": %d", &o_veri->saldiri_gelistirmesi);   
                }
                // Elit eğitim
                char *elit_start = strstr(current, "\"elit_egitim\":");
                if (elit_start && elit_start < ork_end) {
                    sscanf(elit_start, "\"elit_egitim\": %d", &o_veri->elit_egitim);  
                }
                // Savunma ustalığı
                char *savunma_start = strstr(current, "\"savunma_ustaligi\":");
                if (savunma_start && savunma_start < ork_end) {
                    sscanf(savunma_start, "\"savunma_ustaligi\": %d", &o_veri->savunma_ustaligi);
                    }
                // Kuşatma ustalığı
                char *kusatma_start = strstr(current, "\"kusatma_ustaligi\":");
                if (kusatma_start && kusatma_start < ork_end) {
                    sscanf(kusatma_start, "\"kusatma_ustaligi\": %d", &o_veri->kusatma_ustaligi);   
                }}}}}
    void parse_insan_kahr(const char *json, struct InsanVeri *i_veri) {
  // "insan_imparatorlugu" kısmını bul
    char *insan_start = strstr(json, "\"insan_imparatorlugu\":");
    if (insan_start) {
        char *kahramanlar_start = strstr(insan_start, "\"kahramanlar\":");
        if (kahramanlar_start) {
            // Araştırma seviyesinin sonunu bul
            char *insan_end = strstr(kahramanlar_start, "}");
            if (insan_end) {
                // Araştırma seviyesini ayrıştır
                char *current = kahramanlar_start;

                // Savunma ustalığı
                char *kahramanlar_start = strstr(current, "\"kahramanlar\":");
                if (kahramanlar_start && kahramanlar_start < insan_end) {
                    sscanf(kahramanlar_start, "\"kahramanlar\": [\"%[^\"]\"]", i_veri->insankahr);
                }}}}}
    void parse_insan_canavar(const char *json, struct InsanVeri *i_veri) {
    // "insan_imparatorlugu" kısmını bul
    char *insan_start = strstr(json, "\"insan_imparatorlugu\":");
    if (insan_start) {
        char *canavar_start = strstr(insan_start, "\"canavarlar\":");
        if (canavar_start) {
            // Araştırma seviyesinin sonunu bul
            char *insan_end = strstr(canavar_start, "}");
            if (insan_end) {
                // Araştırma seviyesini ayrıştır
                char *current = canavar_start;
                // Savunma ustalığı
                char *canavar_start = strstr(current, "\"canavarlar\":");
                if (canavar_start && canavar_start < insan_end) {
                    sscanf(canavar_start, "\"canavarlar\": [\"%[^\"]\"]", i_veri->insancnvr);
                }}}}}
    void parse_ork_kahr(const char *json, struct OrkVeri *o_veri) {
    // "ork_legi" kısmını bul
    char *ork_start = strstr(json, "\"ork_legi\":");
    if (ork_start) {
        char *kahramanlar_start = strstr(ork_start, "\"kahramanlar\":");
        
        // Kahramanlar mevcut mu kontrol et
        if (kahramanlar_start) {
            // Araştırma seviyesinin sonunu bul
            char *ork_end = strstr(kahramanlar_start, "]");
            if (ork_end) {
                // Kahramanları ayrıştır
                sscanf(kahramanlar_start, "\"kahramanlar\": [\"%[^\"]\"]", o_veri->orkkahr);
            }
        } else {
            // Kahraman yoksa varsayılan bir değer atayın
            strcpy(o_veri->orkkahr, "Yok"); // veya uygun bir varsayılan değer
        }
    } else {
        // ork_legi yoksa uygun bir hata yönetimi yapabilirsiniz
        strcpy(o_veri->orkkahr, "Ork leği bulunamadı");
    }
}
    void parse_ork_canavar(const char *json, struct OrkVeri *o_veri) {
  // "insan_imparatorlugu" kısmını bul
    char *insan_start = strstr(json, "\"ork_legi\":");
    if (insan_start) {
        char *canavar_start = strstr(insan_start, "\"canavarlar\":");
        if (canavar_start) {
            // Araştırma seviyesinin sonunu bul
            char *insan_end = strstr(canavar_start, "}");
            if (insan_end) {
                // Araştırma seviyesini ayrıştır
                char *current = canavar_start;
                // Savunma ustalığı
                char *canavar_start = strstr(current, "\"canavarlar\":");
                if (canavar_start && canavar_start < insan_end) {
                    sscanf(canavar_start, "\"canavarlar\": [\"%[^\"]\"]", o_veri->orkcnvr);
                }}}}}
  

const int ekran_eni = 800;
const int ekran_yukseklik = 800;
const int izgara_sayisi = 40;
const int fotograf_boyut = izgara_sayisi - 2; // Görsel boyutu
#define BİRİM_SAYİ 80 // Birim sayısını sabit olarak tanımla

// Birim verileri
typedef struct {
    int saglik;  // Tamsayı olarak birim ismi
    int birim;
    SDL_Texture* texture;//yapı
    int x_ekseni; // Izgaradaki x pozisyonu
    int y_ekseni; // Izgaradaki y pozisyonu
} Unit;


Unit units[BİRİM_SAYİ]; // 8 birim
Unit units2[BİRİM_SAYİ];
    
// Başlatma fonksiyonu
int init(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL başlatılamadı! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    *window = SDL_CreateWindow("MEYDAN MUHAREBESİ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ekran_eni, ekran_yukseklik, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("Pencere oluşturulamadı! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("Renderer oluşturulamadı! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return -1;
    }

    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        printf("SDL_image başlatılamadı! SDL_image Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(*renderer);
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return -1;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf başlatılamadı! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(*renderer);
        SDL_DestroyWindow(*window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    return 0;
}
// Font yükleme fonksiyonu  
TTF_Font* loadFont(const char* yazitipiPath, int yazitipi_boyutu) {
    TTF_Font* font = TTF_OpenFont(yazitipiPath, yazitipi_boyutu);
    if (font == NULL) {
        printf("Font yüklenemedi! SDL_ttf Error: %s\n", TTF_GetError());
    }
    return font;
}
void renderHealthBar(SDL_Renderer* renderer, int saglik, int x, int y, int en, int boy) {
    // Arka plan (boş bar)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Beyaz arka plan (boş bar)
    SDL_Rect saglikbar_background = {x, y, en, boy};
    SDL_RenderFillRect(renderer, &saglikbar_background);

    // Sağlık değeri 0'dan küçükse bile minimum genişlikte bir bar çizelim
    float saglik_yuzdesi = (float)saglik / 100.0f; // %100 birim, max 100 kabul edildi
    int dolu_hali = (int)(en * (saglik_yuzdesi > 0 ? saglik_yuzdesi : 0.01f)); // Sağlık 0 ise minimum genişlikte çiz

    // Sağlık değerine göre renk atama
    if (saglik >= 80) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Yeşil (80-100 arası)
    } else if (saglik >= 20) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Sarı (30-79 arası)
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Kırmızı (0-29 arası)
    }

    SDL_Rect full_bar = {x, y, dolu_hali, boy};
    SDL_RenderFillRect(renderer, &full_bar);
}
// Görsel yükleme fonksiyonu


SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* yüklü_yüzey = IMG_Load(path);
    if (yüklü_yüzey == NULL) {
        printf("Görsel yüklenemedi! SDL_image Error: %s\n", IMG_GetError());
        return NULL;
    }
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, yüklü_yüzey);
    SDL_FreeSurface(yüklü_yüzey);
    return newTexture;
}




int loadUnits(SDL_Renderer* renderer, insan_sayi *insan,ork_sayi *ork , int p1, int o1, int s1, int k1, int o2, int m1, int t1, int v1) {
    const char* fotografPath[BİRİM_SAYİ] = {
        "Files/okcu.png", "Files/mancinik.png", "Files/piyade.png", "Files/suvari.png",
        "Files/mizrakci.png", "Files/ork_dovuscusu.png", "Files/troll.png", "Files/varg_binici.png"
    };



    int saglik[BİRİM_SAYİ] = {o1, k1, p1, s1, m1, o2, t1, v1}; // Her birim için sağlık değerleri
    int birim_sayisi[BİRİM_SAYİ] = { insan->insanbirimler.okcusayisi,  insan->insanbirimler.kusatmacisayisi,  insan->insanbirimler.piyadesayisi, insan->insanbirimler.suvarisayisi,  ork->orkbirimler.mizrakcisayisi, ork->orkbirimler.orkdovuscusayisi, ork->orkbirimler.trolsayisi,  ork->orkbirimler.vargsayisi}; // Birim sayıları

    int birim_index = 0; // Şu anki birim dizisinin indeksi
    int baslangicX = 0; // Başlangıç sütunu (sol sütundan başlıyor)
    int baslangicY = 0; // Başlangıç satırı (ilk satırdan başlıyor)
    int MAX_sutün_basi_birlik = 20; // Her sütun için maksimum satır sayısı (20)
    int yarim_izgara_sütun = ekran_eni / 2 / izgara_sayisi; // Sol ve sağ grid sütunları ortasından ayıracağız.

    // Sol tarafta ilk 4 birim
    for (int i = 0; i < 4; i++) {
        int kalan_birim = birim_sayisi[i]; // Birimdeki kalan asker sayısı

        // Asker sayısını hücrelere dağıt
        while (kalan_birim > 0) {
            int anlik_birim = (kalan_birim > 100) ? 100 : kalan_birim; // Bir hücreye koyulacak asker sayısı

            // Yeni birim yarat
            units[birim_index].saglik = saglik[i]; // Sağlık değerini atıyoruz
            units[birim_index].birim = anlik_birim;
            units[birim_index].x_ekseni = baslangicX; // Sol taraftaki birimler için X pozisyonu
            units[birim_index].y_ekseni = baslangicY; // Y pozisyonu sabit (aşağıya doğru)

            // Görselleri yükle
            units[birim_index].texture = loadTexture(fotografPath[i], renderer);
            if (units[birim_index].texture == NULL) {
                printf("Görsel yüklenemedi: %s\n", fotografPath[i]);
                return -1;
            }

            // Kalan asker sayısını güncelle
            kalan_birim -= anlik_birim;
            birim_index++; // Bir sonraki birime geç

            // Bir sonraki satıra geç
            baslangicY++;

            // Eğer 20 satıra ulaştıysak, bir sonraki sütuna geç
            if (baslangicY >= MAX_sutün_basi_birlik) {
                baslangicY = 0; // Satırı sıfırla
                baslangicX += 2; // Artık 1 yerine 2 sütun kaydır
            }
        }
    }

    // Sağ tarafta son 4 birim
    baslangicX = yarim_izgara_sütun; // Sağ taraftan başlayacak (grid'in ortasından)
    baslangicY = 0; // Başlangıç satırı sıfırlanır

    for (int i = 4; i < 8; i++) {
        int kalan_birim = birim_sayisi[i]; // Birimdeki kalan asker sayısı

        // Asker sayısını hücrelere dağıt
        while (kalan_birim > 0) {
            int anlik_birim = (kalan_birim > 100) ? 100 : kalan_birim; // Bir hücreye koyulacak asker sayısı

            // Yeni birim yarat
            units[birim_index].saglik = saglik[i]; // Sağlık değerini atıyoruz
            units[birim_index].birim = anlik_birim;
            units[birim_index].x_ekseni = baslangicX; // Sağ taraftaki birimler için X pozisyonu
            units[birim_index].y_ekseni = baslangicY; // Y pozisyonu sabit (aşağıya doğru)

            // Görselleri yükle
            units[birim_index].texture = loadTexture(fotografPath[i], renderer);
            if (units[birim_index].texture == NULL) {
                printf("Görsel yüklenemedi: %s\n", fotografPath[i]);
                return -1;
            }

            // Kalan asker sayısını güncelle
            kalan_birim -= anlik_birim;
            birim_index++; // Bir sonraki birime geç

            // Bir sonraki satıra geç
            baslangicY++;

            // Eğer 20 satıra ulaştıysak, bir sonraki sütuna geç
            if (baslangicY >= MAX_sutün_basi_birlik) {
                baslangicY = 0; // Satırı sıfırla
                baslangicX += 2; // Artık 1 yerine 2 sütun kaydır
            }
        }
    }

    return 0;
}
int loadUnits2(SDL_Renderer* renderer, insan_sayi *insan, ork_sayi *ork , int p1, int o1, int s1, int k1, int o2, int m1, int t1, int v1) {
    const char* fotografPath[BİRİM_SAYİ] = {
        "Files/okcu.png", "Files/mancinik.png", "Files/piyade.png", "Files/suvari.png",
        "Files/mizrakci.png", "Files/ork_dovuscusu.png", "Files/troll.png", "Files/varg_binici.png"
    };




    int saglik[BİRİM_SAYİ] = {o1, k1, p1, s1, m1, o2, t1, v1};
    int birim_sayisi[BİRİM_SAYİ] = {
        insan->insanbirimler.okcusayisi,
        insan->insanbirimler.kusatmacisayisi,
        insan->insanbirimler.piyadesayisi,
        insan->insanbirimler.suvarisayisi,
        ork->orkbirimler.mizrakcisayisi,
        ork->orkbirimler.orkdovuscusayisi,
        ork->orkbirimler.trolsayisi,
        ork->orkbirimler.vargsayisi
    };


    int birim_index = 0;
    int baslangicX = 0;
    int baslangicY = 0;
    int MAX_sutün_basi_birlik = 20;
    int yarim_izgara_sütun = ekran_eni / 2 / izgara_sayisi;

    // Sol tarafta ilk 4 birim
    for (int i = 0; i < 4; i++) {
        int kalan_birim = birim_sayisi[i];

        // Sağlık ve birim sayısını kontrol et
        if (saglik[i] <= 0 || kalan_birim <= 0) continue;

        while (kalan_birim > 0) {
            int anlik_birim = (kalan_birim > 100) ? 100 : kalan_birim;

            // Yeni birim yarat
            units2[birim_index].saglik = saglik[i];
            units2[birim_index].birim = anlik_birim;
            units2[birim_index].x_ekseni = baslangicX;
            units2[birim_index].y_ekseni = baslangicY;

            units2[birim_index].texture = loadTexture(fotografPath[i], renderer);
            if (units2[birim_index].texture == NULL) {
                printf("Görsel yüklenemedi: %s\n", fotografPath[i]);
                return -1;
            }

            kalan_birim -= anlik_birim;
            birim_index++;
            baslangicY++;

            if (baslangicY >= MAX_sutün_basi_birlik) {
                baslangicY = 0;
                baslangicX += 2;
            }
        }
    }


    // Sağ tarafta son 4 birim
    baslangicX = yarim_izgara_sütun;
    baslangicY = 0;

    for (int i = 4; i < 8; i++) {
        int kalan_birim = birim_sayisi[i];

        // Sağlık ve birim sayısını kontrol et
        if (saglik[i] <= 0 || kalan_birim <= 0) continue;

        while (kalan_birim > 0) {
            int anlik_birim = (kalan_birim > 100) ? 100 : kalan_birim;

            units2[birim_index].saglik = saglik[i];
            units2[birim_index].birim = anlik_birim;
            units2[birim_index].x_ekseni = baslangicX;
            units2[birim_index].y_ekseni = baslangicY;

            units2[birim_index].texture = loadTexture(fotografPath[i], renderer);
            if (units[birim_index].texture == NULL) {
                printf("Görsel yüklenemedi: %s\n", fotografPath[i]);
                return -1;
            }

            kalan_birim -= anlik_birim;
            birim_index++;
            baslangicY++;

            if (baslangicY >= MAX_sutün_basi_birlik) {
                baslangicY = 0;
                baslangicX += 2;
            }
        }
    }
   
    return 0;
}




// Yazıyı render etme fonksiyonu
void renderText(SDL_Renderer* renderer, TTF_Font* font, int birim, int x_ekseni, int y_ekseni) {
    SDL_Color textColor = {0, 0, 0, 255}; // Siyah renk
    char text[10]; // Sayı için yeterli boyutta bir dizi
    sprintf(text, "%d", birim); // Sadece birim sayısını yazdır
    SDL_Surface* metin_yuzeyi = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* metin_Texture = SDL_CreateTextureFromSurface(renderer, metin_yuzeyi);
    int texten = metin_yuzeyi->w;
    int textboy = metin_yuzeyi->h;
    SDL_FreeSurface(metin_yuzeyi);

    // Yazı için konum belirleme
    int textX = (x_ekseni + 1) * izgara_sayisi + (izgara_sayisi - texten) / 2; // Görüntünün bulunduğu hücreden 2 ızgara sağa
    int textY = y_ekseni * izgara_sayisi + (izgara_sayisi - textboy) / 2; // Görüntüyle dikey ortalanmış şekilde

    SDL_Rect renderQuad = {textX, textY, texten, textboy};
    SDL_RenderCopy(renderer, metin_Texture, NULL, &renderQuad);
    SDL_DestroyTexture(metin_Texture);
}
void drawGrid(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_SetRenderDrawColor(renderer, 104 , 149, 210,255); // altın sol dikdörtgen
    SDL_Rect sol_kisim = {0, 0, ekran_eni / 2, ekran_yukseklik};
    SDL_RenderFillRect(renderer, &sol_kisim);

    SDL_SetRenderDrawColor(renderer, 208, 72, 72, 255); // yeşil sağ dikdörtgen
    SDL_Rect sag_kisim = {ekran_eni / 2, 0, ekran_eni / 2, ekran_yukseklik};
    SDL_RenderFillRect(renderer, &sag_kisim);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Siyah çizgiler
    for (int y = 0; y < ekran_yukseklik; y += izgara_sayisi) {
        for (int x = 0; x < ekran_eni; x += izgara_sayisi) {
            SDL_Rect kare_izgara = {x + 1, y + 1, izgara_sayisi - 1, izgara_sayisi - 1};
            SDL_RenderDrawRect(renderer, &kare_izgara);
        }
    }

    // Görselleri ve isimleri ızgarada çiz
    for (int i = 0; i < BİRİM_SAYİ; i++) {
        // Sağlık değeri 0 ise devam et, birim çizilmesin
        if (units[i].saglik == 0) {
            continue;
        }

        int imgX = units[i].x_ekseni * izgara_sayisi + (izgara_sayisi - fotograf_boyut) / 2;
        int imgY = units[i].y_ekseni * izgara_sayisi + (izgara_sayisi - fotograf_boyut) / 2;

        SDL_Rect imgRect = {imgX, imgY, fotograf_boyut, fotograf_boyut};
        SDL_RenderCopy(renderer, units[i].texture, NULL, &imgRect);

        // Birim sayılarını yazdır (2 ızgara sağa kaydırılmış hali)
        renderText(renderer, font, units[i].birim, units[i].x_ekseni, units[i].y_ekseni);

        // Sağlık barı render edilir
        renderHealthBar(renderer, units[i].saglik, imgX + 1, imgY + 1, fotograf_boyut, 5);
    }
}
void drawGrid2(SDL_Renderer* renderer, TTF_Font* font) {

   
    SDL_SetRenderDrawColor(renderer, 104 , 39, 210,255); // altın sol dikdörtgen
    SDL_Rect sol_kisim = {0, 0, ekran_eni / 2, ekran_yukseklik};
    SDL_RenderFillRect(renderer, &sol_kisim);

    SDL_SetRenderDrawColor(renderer, 208, 139, 72, 255); // yeşil sağ dikdörtgen
    SDL_Rect sag_kisim = {ekran_eni / 2, 0, ekran_eni / 2, ekran_yukseklik};
    SDL_RenderFillRect(renderer, &sag_kisim);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Siyah çizgiler
    for (int y = 0; y < ekran_yukseklik; y += izgara_sayisi) {
        for (int x = 0; x < ekran_eni; x += izgara_sayisi) {
            SDL_Rect kare_izgara = {x + 1, y + 1, izgara_sayisi - 1, izgara_sayisi - 1};
            SDL_RenderDrawRect(renderer, &kare_izgara);
        }
    }

    // Görselleri ve isimleri ızgarada çiz
    for (int i = 0; i < BİRİM_SAYİ; i++) {
        // Sağlık değeri 0 ise devam et, birim çizilmesin
        if (units2[i].birim <= 0) {
            
            i++;
        }
        else
        {
        int imgX = units2[i].x_ekseni * izgara_sayisi + (izgara_sayisi - fotograf_boyut) / 2;
        int imgY = units2[i].y_ekseni * izgara_sayisi + (izgara_sayisi - fotograf_boyut) / 2;




        SDL_Rect imgRect = {imgX, imgY, fotograf_boyut, fotograf_boyut};
        SDL_RenderCopy(renderer, units2[i].texture, NULL, &imgRect);
        if(units2[i].saglik > 0)
        // Birim sayılarını yazdır (2 ızgara sağa kaydırılmış hali)
       { renderText(renderer, font, units2[i].birim, units2[i].x_ekseni, units2[i].y_ekseni);}
    if(units2[i].saglik > 0 )
        // Sağlık barı render edilir
        {renderHealthBar(renderer, units2[i].saglik, imgX + 1, imgY + 1, fotograf_boyut, 5);}
        }

        
    }
}

// Bellek temizleme fonksiyonu
void cleanup(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font) {
    for (int i = 0; i < BİRİM_SAYİ; i++) {
        SDL_DestroyTexture(units[i].texture);
    }
    if (font != NULL) {
        TTF_CloseFont(font);
    }
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int main(int argc, char* args[]) {
        insan_imp insan_imparatorlugu = {0};  
        ork_legion ork_legi = {0};
        insan_kahr insan_kahraman = {0} ;
        ork_kahr ork_kahraman = {0};
        insan_canavar insan_cnv = {0};
        ork_canavar ork_cnv ={0};
        savunma_ustasi savunma_level = {0};
        saldiri_gelistirmesi saldiri_level = {0};
        elit_egitim egitim_level = {0};
        kusatma_ustaligi kusatma_level = {0};
        insan_sayi birim1 = {0};
        ork_sayi birim2 = {0};
        struct InsanVeri i_veri = {0};
        struct OrkVeri o_veri = {0};
// degerlerin parse edilmesi

            char dosya_uzunluk[MAX_dosya_uzunluk_LENGTH];
// insan imp birimleri
FILE *file_type = fopen("C:\\users\\minth\\Documents\\VSCODE\\JSONLAR\\unit_types.json", "r");
    if (file_type== NULL) {
            printf("insanbirim açılamadı.\n");
            return 1;}
    while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_type)) {
            while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_type)) {
        if (strstr(dosya_uzunluk, "insan_imparatorlugu")) {
            while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_type)) {
                if (strstr(dosya_uzunluk, "piyadeler")) {
                    degiskenAyir(file_type, &insan_imparatorlugu.piyadeler);
                }else if (strstr(dosya_uzunluk, "okcular")) {
                    degiskenAyir(file_type, &insan_imparatorlugu.okcular);          
                }else if (strstr(dosya_uzunluk, "suvariler")) {
                    degiskenAyir(file_type, &insan_imparatorlugu.suvariler);    
                }else if (strstr(dosya_uzunluk, "kusatma_makineleri")) {
                    degiskenAyir(file_type, &insan_imparatorlugu.kusatma_makineleri);  
                    }}}}}
    fclose(file_type);
// ork legi birimleri
   FILE *file_type2 = fopen("C:\\users\\minth\\Documents\\VSCODE\\JSONLAR\\unit_types.json", "r");
    if (file_type2 == NULL) {
            printf("orkbirim acilmadi\n");
            return 1;}
    while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_type2)) {
        while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_type2)) {
        if (strstr(dosya_uzunluk, "ork_legi")) {
            while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_type2)) {
                if (strstr(dosya_uzunluk, "ork_dovusculeri")) {
                    degiskenAyir(file_type, &ork_legi.ork_dovusculeri);
                } else if (strstr(dosya_uzunluk, "mizrakcilar")) {
                    degiskenAyir(file_type, &ork_legi.mizrakcilar);
                } else if (strstr(dosya_uzunluk, "varg_binicileri")) {
                    degiskenAyir(file_type, &ork_legi.varg_binicileri);
                } else if (strstr(dosya_uzunluk, "troller")) {
                    degiskenAyir(file_type, &ork_legi.troller);
                }}}}}
    fclose(file_type2);
//insan imp kahramanlar 
    FILE *file_heroes = fopen("C:\\users\\minth\\Documents\\VSCODE\\JSONLAR\\heroes.json", "r");
    if (file_heroes == NULL) {
            printf("isnanKomutan dosyası açılamadı.\n");
            return 1;}
    while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_heroes)) {
            while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_heroes)) {
        if (strstr(dosya_uzunluk, "insan_imparatorlugu")) {
            while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_heroes)) {
                if (strstr(dosya_uzunluk, "Alparslan")) {
                    komutanAyir(file_heroes, &insan_kahraman.Alparslan);
                }else if (strstr(dosya_uzunluk, "Fatih_Sultan_Mehmet")) {
                    komutanAyir(file_heroes, &insan_kahraman.Fatih_Sultan_Mehmet);          
                }else if (strstr(dosya_uzunluk, "Yavuz_Sultan_Selim")) {
                    komutanAyir(file_heroes, &insan_kahraman.Yavuz_Sultan_Selim);    
                }else if (strstr(dosya_uzunluk, "Mete_Han")) {
                    komutanAyir(file_heroes, &insan_kahraman.Mete_Han);  
                }   else if (strstr(dosya_uzunluk, "Tugrul_Bey")) {
                    komutanAyir(file_heroes, &insan_kahraman.Tugrul_Bey);
                    }}}}}
    fclose(file_heroes);
//ork legi kahramanlar
    FILE *file_heroes2 = fopen("C:\\users\\minth\\Documents\\VSCODE\\JSONLAR\\heroes.json", "r");
    if (file_heroes2 == NULL) {
            printf("orkKomutan dosyası açılamadı.\n");
            return 1;}
    while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_heroes2)) {
            // Ork Lejyonu komutanlarını ayrıştır
            if (strstr(dosya_uzunluk, "ork_legi")) {
                while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_heroes2)) {
                    if (strstr(dosya_uzunluk, "Goruk_Vahsi")) {
                        komutanAyir(file_heroes2, &ork_kahraman.Goruk_Vahsi);
                    } else if (strstr(dosya_uzunluk, "Thruk_Kemikkiran")) {
                        komutanAyir(file_heroes2, &ork_kahraman.Thruk_Kemikkiran);
                    } else if (strstr(dosya_uzunluk, "Vrog_Kafakiran")) {
                        komutanAyir(file_heroes2, &ork_kahraman.Vrog_Kafakiran);
                    } else if (strstr(dosya_uzunluk, "Ugar_Zalim")) {
                        komutanAyir(file_heroes2, &ork_kahraman.Ugar_Zalim);
                        }}}}
    fclose(file_heroes2);
//insan imp yaratiklar
    FILE *file_creatures = fopen("C:\\users\\minth\\Documents\\VSCODE\\JSONLAR\\creatures.json", "r");
    if (file_creatures == NULL) {
            printf("insancanavar dosyası açılamadı.\n");
            return 1;}
    while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_creatures)) {
            while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_creatures)) {
        if (strstr(dosya_uzunluk, "insan_imparatorlugu")) {
            while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_creatures)) {
                if (strstr(dosya_uzunluk, "Ejderha")) {
                    canavarAyir(file_creatures, &insan_cnv.Ejderha);
                }else if (strstr(dosya_uzunluk, "Agri_Dagi_Devleri")) {
                    canavarAyir(file_creatures, &insan_cnv.Agri_Dagi_Devleri);          
                }else if (strstr(dosya_uzunluk, "Tepegoz")) {
                    canavarAyir(file_creatures, &insan_cnv.Tepegoz);    
                }else if (strstr(dosya_uzunluk, "Karakurt")) {
                    canavarAyir(file_creatures, &insan_cnv.Karakurt);  
                }   else if (strstr(dosya_uzunluk, "Samur")) {
                    canavarAyir(file_creatures, &insan_cnv.Samur);
                    }}}}}
    fclose(file_creatures);
//ork legi yaratiklar
    FILE *file_creatures2 = fopen("C:\\users\\minth\\Documents\\VSCODE\\JSONLAR\\creatures.json", "r");
    if (file_creatures2 == NULL) {
            printf("orkcanavar dosyası açılamadı.\n");
            return 1;}
    while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_creatures2)) {
            // Ork Lejyonu komutanlarını ayrıştır
            if (strstr(dosya_uzunluk, "ork_legi")) {
                while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_creatures2)) {
                    if (strstr(dosya_uzunluk, "Kara_Troll")) {
                        canavarAyir(file_creatures2, &ork_cnv.Kara_Troll);
                    } else if (strstr(dosya_uzunluk, "Golge_Kurtlari")) {
                        canavarAyir(file_creatures2, &ork_cnv.Golge_Kurtlari);
                    } else if (strstr(dosya_uzunluk, "Camur_Devleri")) {
                        canavarAyir(file_creatures2, &ork_cnv.Camur_Devleri);
                    } else if (strstr(dosya_uzunluk, "Ates_Iblisi")) {
                        canavarAyir(file_creatures2, &ork_cnv.Ates_Iblisi);
                    } else if (strstr(dosya_uzunluk, "Buz_Devleri")) {
                        canavarAyir(file_creatures2, &ork_cnv.Buz_Devleri);
                    }}}}
    fclose(file_creatures2);
//savunma arastirma
    FILE *file_research = fopen("C:\\users\\minth\\Documents\\VSCODE\\JSONLAR\\research.json", "r");
    if (file_research == NULL) {
            printf("arastirma1 dosyası açılamadı.\n");
            return 1;}
    while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_research)) {
            if (strstr(dosya_uzunluk, "savunma_ustaligi")) {
                while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_research)) {
                    if (strstr(dosya_uzunluk, "seviye_1")) {
                        researchAyir(file_research, &savunma_level.seviye_1);
                    } else if (strstr(dosya_uzunluk, "seviye_2")) {
                        researchAyir(file_research, &savunma_level.seviye_2);
                    } else if (strstr(dosya_uzunluk, "seviye_3")) {
                        researchAyir(file_research, &savunma_level.seviye_3);
                        break;}}}}
    fclose(file_research);
//saldiri arastirma
    FILE *file_research2 = fopen("C:\\users\\minth\\Documents\\VSCODE\\JSONLAR\\research.json", "r");
    if (file_research2 == NULL) {
            printf("arastirma2 dosyası açılamadı.\n");
            return 1;}
    while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_research2)) {
            if (strstr(dosya_uzunluk, "saldiri_gelistirmesi")) {
                while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_research)) {
                    if (strstr(dosya_uzunluk, "seviye_1")) {
                        researchAyir(file_research2, &saldiri_level.seviye_1);
                    } else if (strstr(dosya_uzunluk, "seviye_2")) {
                        researchAyir(file_research2, &saldiri_level.seviye_2);
                    } else if (strstr(dosya_uzunluk, "seviye_3")) {
                        researchAyir(file_research2, &saldiri_level.seviye_3);
                        break;}}}}
    fclose(file_research2);
//elit egitim arastirma
    FILE *file_research3 = fopen("C:\\users\\minth\\Documents\\VSCODE\\JSONLAR\\research.json", "r");
    if (file_research3 == NULL) {
            printf("arastirma3 dosyası açılamadı.\n");
            return 1;}
    while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_research3)) {
            if (strstr(dosya_uzunluk, "elit_egitim")) {
                while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_research3)) {
                    if (strstr(dosya_uzunluk, "seviye_1")) {
                        researchAyir(file_research3, &egitim_level.seviye_1);
                    } else if (strstr(dosya_uzunluk, "seviye_2")) {
                        researchAyir(file_research3, &egitim_level.seviye_2);
                    } else if (strstr(dosya_uzunluk, "seviye_3")) {
                        researchAyir(file_research3, &egitim_level.seviye_3);
                        break;}}}}
    fclose(file_research3);
//kusatma arastirma
    FILE *file_research4 = fopen("C:\\users\\minth\\Documents\\VSCODE\\JSONLAR\\research.json", "r");
    if (file_research4 == NULL) {
            printf("arastirma4 dosyası açılamadı.\n");
            return 1;}
    while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_research4)) {
            if (strstr(dosya_uzunluk, "kusatma_ustaligi")) {
                while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_research4)) {
                    if (strstr(dosya_uzunluk, "seviye_1")) {
                        researchAyir(file_research4, &kusatma_level.seviye_1);
                    } else if (strstr(dosya_uzunluk, "seviye_2")) {
                        researchAyir(file_research4, &kusatma_level.seviye_2);
                    } else if (strstr(dosya_uzunluk, "seviye_3")) {
                        researchAyir(file_research4, &kusatma_level.seviye_3);
                        break;}}}}
    fclose(file_research4);



CURL *curl;
    CURLcode res;



    curl = curl_easy_init();
    if (curl) {
         FILE *fp = fopen("C:\\users\\minth\\Documents\\VSCODE\\veri.json", "wb");
        if (fp == NULL) {
            fprintf(stderr, "Dosya açma hatası\n");
            return 1;
        }

        curl_easy_setopt(curl, CURLOPT_URL,  "https://yapbenzet.org.tr/5.json");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() başarısız: %s\n", curl_easy_strerror(res));
        }

        fclose(fp);
        curl_easy_cleanup(curl);
    }


    FILE *file_senaryo = fopen("C:\\users\\minth\\Documents\\VSCODE\\veri.json", "r");
    if (file_senaryo== NULL) {
            printf("insanbirim açılamadı.\n");
            return 1;}
    while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_senaryo)) {
            while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_senaryo)) {
        if (strstr(dosya_uzunluk, "insan_imparatorlugu")) {
            while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_senaryo)) {
                if (strstr(dosya_uzunluk, "birimler")) {
                    senaryo1Ayir(file_senaryo, &birim1.insanbirimler);}}}}}
    fclose(file_senaryo);

  FILE *file_senaryo2 = fopen("C:\\users\\minth\\Documents\\VSCODE\\veri.json", "r");
    if (file_senaryo2== NULL) {
            printf("insanbirim açılamadı.\n");
            return 1;}
    while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_senaryo2)) {
            while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_senaryo2)) {
        if (strstr(dosya_uzunluk, "ork_legi")) {
            while (fgets(dosya_uzunluk, sizeof(dosya_uzunluk), file_senaryo2)) {
                if (strstr(dosya_uzunluk, "birimler")) {
                    senaryo1Ayir(file_senaryo2, &birim2.orkbirimler);
                    break; }}}}}
    fclose(file_senaryo2);

FILE *file = fopen("C:\\users\\minth\\Documents\\VSCODE\\veri.json", "r");
    if (!file) {
        perror("Dosya açılamadı");
        return EXIT_FAILURE;}
    // Dosya boyutunu öğren
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Bellekte yeterli yer ayır
    char *json_data = malloc(length + 1);
    fread(json_data, 1, length, file);
    json_data[length] = '\0'; // Null terminator ekle
    fclose(file);

    // JSON verilerini ayrıştır
    parse_insan(json_data, &i_veri);
    parse_ork(json_data, &o_veri);
    parse_insan_kahr(json_data, &i_veri);
    parse_insan_canavar(json_data, &i_veri);
    parse_ork_kahr(json_data, &o_veri);
    parse_ork_canavar(json_data, &o_veri);
// birimlerle carpma + kahraman-canavar etkisi + arastirma
//  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float piyadenetsaldiri= (insan_imparatorlugu.piyadeler.saldiri * birim1.insanbirimler.piyadesayisi);
float suvarinetsaldiri = (insan_imparatorlugu.suvariler.saldiri * birim1.insanbirimler.suvarisayisi);
float okcunetsaldiri = (insan_imparatorlugu.okcular.saldiri * birim1.insanbirimler.okcusayisi);
float kusatmanetsaldiri = (insan_imparatorlugu.kusatma_makineleri.saldiri * birim1.insanbirimler.kusatmacisayisi);
float orkdovuscunetsaldiri = (ork_legi.ork_dovusculeri.saldiri * birim2.orkbirimler.orkdovuscusayisi);
float mizrakcinetsaldiri= (ork_legi.mizrakcilar.saldiri * birim2.orkbirimler.mizrakcisayisi);
float vargnetsaldiri = (ork_legi.varg_binicileri.saldiri * birim2.orkbirimler.vargsayisi);
float trolnetsaldiri = (ork_legi.troller.saldiri * birim2.orkbirimler.trolsayisi);
float piyadenetsavunma = (insan_imparatorlugu.piyadeler.savunma * birim1.insanbirimler.piyadesayisi);
float suvarinetsavunma = (insan_imparatorlugu.suvariler.savunma * birim1.insanbirimler.suvarisayisi);
float okcunetsavunma= (insan_imparatorlugu.okcular.savunma * birim1.insanbirimler.okcusayisi);
float kusatmanetsavunma = (insan_imparatorlugu.kusatma_makineleri.savunma * birim1.insanbirimler.kusatmacisayisi);
float orkdovuscunetsavunma = (ork_legi.ork_dovusculeri.savunma * birim2.orkbirimler.orkdovuscusayisi);
float mizrakcinetsavunma = (ork_legi.mizrakcilar.savunma * birim2.orkbirimler.mizrakcisayisi);
float vargnetsavunma = (ork_legi.varg_binicileri.savunma * birim2.orkbirimler.vargsayisi);
float trolnetsavunma = (ork_legi.troller.savunma * birim2.orkbirimler.trolsayisi);
float piyadenetsaglik= (insan_imparatorlugu.piyadeler.saglik * birim1.insanbirimler.piyadesayisi);
float suvarinetsaglik = (insan_imparatorlugu.suvariler.saglik * birim1.insanbirimler.suvarisayisi);
float okcunetsaglik = (insan_imparatorlugu.okcular.saglik * birim1.insanbirimler.okcusayisi);
float kusatmanetsaglik = (insan_imparatorlugu.kusatma_makineleri.saglik * birim1.insanbirimler.kusatmacisayisi);
float orkdovuscunetsaglik = (ork_legi.ork_dovusculeri.saglik * birim2.orkbirimler.orkdovuscusayisi);
float mizrakcinetsaglik= (ork_legi.mizrakcilar.saglik * birim2.orkbirimler.mizrakcisayisi);
float vargnetsaglik = (ork_legi.varg_binicileri.saglik * birim2.orkbirimler.vargsayisi);
float trolnetsaglik = (ork_legi.troller.saglik * birim2.orkbirimler.trolsayisi);
float alpbonus= atof(insan_kahraman.Alparslan.bonus_degeri);
float fatihbonus= atof(insan_kahraman.Fatih_Sultan_Mehmet.bonus_degeri);
float metebonus = atof(insan_kahraman.Mete_Han.bonus_degeri);
float yavuzbonus = atof(insan_kahraman.Yavuz_Sultan_Selim.bonus_degeri);
float tugrulbonus = atof(insan_kahraman.Tugrul_Bey.bonus_degeri);
float gorukbonus = atof(ork_kahraman.Goruk_Vahsi.bonus_degeri);
float thrukbonus = atof(ork_kahraman.Thruk_Kemikkiran.bonus_degeri);
float vrogbonus = atof(ork_kahraman.Vrog_Kafakiran.bonus_degeri);
float ugarbonus = atof(ork_kahraman.Ugar_Zalim.bonus_degeri);
float ejderbonus = atof(insan_cnv.Ejderha.etki_degeri);
float agribonus = atof(insan_cnv.Agri_Dagi_Devleri.etki_degeri);
float tepegozbonus=atof(insan_cnv.Tepegoz.etki_degeri);
float samurbonus = atof(insan_cnv.Samur.etki_degeri);
float karakurtbonus = atof(insan_cnv.Karakurt.etki_degeri);
float karatrolbonus =atof(ork_cnv.Kara_Troll.etki_degeri);
float golgekurtbonus=atof(ork_cnv.Kara_Troll.etki_degeri);
float camurbonus=atof(ork_cnv.Camur_Devleri.etki_degeri);
float atesiblisbonus=atof(ork_cnv.Ates_Iblisi.etki_degeri);
float buzdevbonus=atof(ork_cnv.Buz_Devleri.etki_degeri);
float savunmaarastirma1=atof(savunma_level.seviye_1.deger);
float savunmaarastirma2=atof(savunma_level.seviye_2.deger);
float savunmaarastirma3=atof(savunma_level.seviye_3.deger);
float saldiriarastirma1=atof(saldiri_level.seviye_1.deger);
float saldiriarastirma2=atof(saldiri_level.seviye_2.deger);
float saldiriarastirma3=atof(saldiri_level.seviye_3.deger);
float elitegitim1=atof(egitim_level.seviye_1.deger);
float elitegitim2=atof(egitim_level.seviye_2.deger);
float elitegitim3=atof(egitim_level.seviye_3.deger);
float kusatmaarastirma1=atof(kusatma_level.seviye_1.deger);
float kusatmaarastirma2=atof(kusatma_level.seviye_2.deger);
float kusatmaarastirma3=atof(kusatma_level.seviye_3.deger);


// insan kahraman etkileri uygulama
int c=1;
if(c==1){
    // alparslan
if (strcmp(i_veri.insankahr, "Alparslan") == 0) {
    // piyade
     if (strcmp(insan_kahraman.Alparslan.aciklamakahr, "piyadelere") == 0) {
         if (strcmp(insan_kahraman.Alparslan.bonus_turu, "saldiri") == 0) {
        piyadenetsaldiri = piyadenetsaldiri * (100 + alpbonus)/100;
      } else if (strcmp(insan_kahraman.Alparslan.bonus_turu, "savunma") == 0) {
        piyadenetsavunma=piyadenetsavunma* (100 + alpbonus)/100;
      } else if (strcmp(insan_kahraman.Alparslan.bonus_turu, "kritik_sans") == 0) {
        insan_imparatorlugu.piyadeler.kritik_sans = insan_imparatorlugu.piyadeler.kritik_sans * (100 + alpbonus)/100;

    }

    // okcu
    } else if (strcmp(insan_kahraman.Alparslan.aciklamakahr, "okcularin") == 0) {
         if (strcmp(insan_kahraman.Alparslan.bonus_turu, "saldiri") == 0) {
        okcunetsaldiri = okcunetsaldiri * (100 + alpbonus)/100;
      } else if (strcmp(insan_kahraman.Alparslan.bonus_turu, "savunma") == 0) {
        okcunetsavunma = okcunetsavunma * (100 + alpbonus)/100;
      } else if (strcmp(insan_kahraman.Alparslan.bonus_turu, "kritik_sans") == 0) {
        insan_imparatorlugu.okcular.kritik_sans = insan_imparatorlugu.okcular.kritik_sans * (100+ alpbonus)/100;
    }

    // suvari
    } else if (strcmp(insan_kahraman.Alparslan.aciklamakahr, "suvarilere") == 0) {
         if (strcmp(insan_kahraman.Alparslan.bonus_turu, "saldiri") == 0) {
        suvarinetsaldiri = suvarinetsaldiri * (100 + alpbonus)/100;
      } else if (strcmp(insan_kahraman.Alparslan.bonus_turu, "savunma") == 0) {
        suvarinetsavunma = suvarinetsavunma * (100 + alpbonus)/100;
      } else if (strcmp(insan_kahraman.Alparslan.bonus_turu, "kritik_sans") == 0) {
        insan_imparatorlugu.suvariler.kritik_sans = insan_imparatorlugu.suvariler.kritik_sans * (100 + alpbonus)/100;
    }

    // kusatma
    } else if (strcmp(insan_kahraman.Alparslan.aciklamakahr, "kusatma_makinelerinin") == 0) {
         if (strcmp(insan_kahraman.Alparslan.bonus_turu, "saldiri") == 0) {
        kusatmanetsaldiri = kusatmanetsaldiri * (100 + alpbonus)/100;
      } else if (strcmp(insan_kahraman.Alparslan.bonus_turu, "savunma") == 0) {
        kusatmanetsavunma = kusatmanetsaldiri *(100 + alpbonus)/100;
      } else if (strcmp(insan_kahraman.Alparslan.bonus_turu, "kritik_sans") == 0) {
        insan_imparatorlugu.kusatma_makineleri.kritik_sans = insan_imparatorlugu.kusatma_makineleri.kritik_sans * (100 + alpbonus)/100;
    }
    }
 }

// fatih
if (strcmp(i_veri.insankahr, "Fatih_Sultan_Mehmet") == 0) {
    // piyade
     if (strcmp(insan_kahraman.Fatih_Sultan_Mehmet.aciklamakahr, "piyadelere") == 0) {
         if (strcmp(insan_kahraman.Fatih_Sultan_Mehmet.bonus_turu, "saldiri") == 0) {
        piyadenetsaldiri = piyadenetsaldiri * (100 + fatihbonus)/100;
      } else if (strcmp(insan_kahraman.Fatih_Sultan_Mehmet.bonus_turu, "savunma") == 0) {
        piyadenetsavunma=piyadenetsavunma* (100 + fatihbonus)/100;
      } else if (strcmp(insan_kahraman.Fatih_Sultan_Mehmet.bonus_turu, "kritik_sans") == 0) {
        insan_imparatorlugu.piyadeler.kritik_sans = insan_imparatorlugu.piyadeler.kritik_sans * (100 + fatihbonus)/100;
    }

    // okcu
    } else if (strcmp(insan_kahraman.Fatih_Sultan_Mehmet.aciklamakahr, "okcularin") == 0) {
         if (strcmp(insan_kahraman.Fatih_Sultan_Mehmet.bonus_turu, "saldiri") == 0) {
        okcunetsaldiri = okcunetsaldiri * (100 + fatihbonus)/100;
      } else if (strcmp(insan_kahraman.Fatih_Sultan_Mehmet.bonus_turu, "savunma") == 0) {
        okcunetsavunma = okcunetsavunma * (100 + fatihbonus)/100;
      } else if (strcmp(insan_kahraman.Fatih_Sultan_Mehmet.bonus_turu, "kritik_sans") == 0) {
       insan_imparatorlugu.okcular.kritik_sans = insan_imparatorlugu.okcular.kritik_sans * (100 + fatihbonus)/100;;
    }

    // suvari
    } else if (strcmp(insan_kahraman.Fatih_Sultan_Mehmet.aciklamakahr, "suvarilere") == 0) {
         if (strcmp(insan_kahraman.Fatih_Sultan_Mehmet.bonus_turu, "saldiri") == 0) {
        suvarinetsaldiri = suvarinetsaldiri * (100 + fatihbonus)/100;
      } else if (strcmp(insan_kahraman.Fatih_Sultan_Mehmet.bonus_turu, "savunma") == 0) {
        suvarinetsavunma = suvarinetsavunma * (100 + fatihbonus)/100;
      } else if (strcmp(insan_kahraman.Fatih_Sultan_Mehmet.bonus_turu, "kritik_sans") == 0) {
        insan_imparatorlugu.suvariler.kritik_sans = insan_imparatorlugu.suvariler.kritik_sans * (100 + fatihbonus)/100;;
    }

    // kusatma
    } else if (strcmp(insan_kahraman.Fatih_Sultan_Mehmet.aciklamakahr, "kusatma_makinelerinin") == 0) {
         if (strcmp(insan_kahraman.Fatih_Sultan_Mehmet.bonus_turu, "saldiri") == 0) {
        kusatmanetsaldiri = kusatmanetsaldiri * (100 + fatihbonus)/100;
      } else if (strcmp(insan_kahraman.Fatih_Sultan_Mehmet.bonus_turu, "savunma") == 0) {
        kusatmanetsavunma = kusatmanetsaldiri *(100 + fatihbonus)/100;
      } else if (strcmp(insan_kahraman.Fatih_Sultan_Mehmet.bonus_turu, "kritik_sans") == 0) {
         insan_imparatorlugu.kusatma_makineleri.kritik_sans = insan_imparatorlugu.kusatma_makineleri.kritik_sans * (100 + fatihbonus)/100;;
 
    }
    }
 }

// yavuz
if (strcmp(i_veri.insankahr, "Yavuz_Sultan_Selim") == 0) {
    // piyade
     if (strcmp(insan_kahraman.Yavuz_Sultan_Selim.aciklamakahr, "piyadelere") == 0) {
         if (strcmp(insan_kahraman.Yavuz_Sultan_Selim.bonus_turu, "saldiri") == 0) {
        piyadenetsaldiri = piyadenetsaldiri * (100 + yavuzbonus)/100;
      } else if (strcmp(insan_kahraman.Yavuz_Sultan_Selim.bonus_turu, "savunma") == 0) {
        piyadenetsavunma=piyadenetsavunma* (100 + yavuzbonus)/100;
      } else if (strcmp(insan_kahraman.Yavuz_Sultan_Selim.bonus_turu, "kritik_sans") == 0) {
         insan_imparatorlugu.piyadeler.kritik_sans = insan_imparatorlugu.piyadeler.kritik_sans * (100 + yavuzbonus)/100;
 
    }

    // okcu
    } else if (strcmp(insan_kahraman.Yavuz_Sultan_Selim.aciklamakahr, "okcularin") == 0) {
         if (strcmp(insan_kahraman.Yavuz_Sultan_Selim.bonus_turu, "saldiri") == 0) {
        okcunetsaldiri = okcunetsaldiri * (100 + yavuzbonus)/100;
      } else if (strcmp(insan_kahraman.Yavuz_Sultan_Selim.bonus_turu, "savunma") == 0) {
        okcunetsavunma = okcunetsavunma * (100 + yavuzbonus)/100;
      } else if (strcmp(insan_kahraman.Yavuz_Sultan_Selim.bonus_turu, "kritik_sans") == 0) {
         insan_imparatorlugu.okcular.kritik_sans = insan_imparatorlugu.okcular.kritik_sans * (100 + yavuzbonus)/100;
 
    }

    // suvari
    } else if (strcmp(insan_kahraman.Yavuz_Sultan_Selim.aciklamakahr, "suvarilere") == 0) {
         if (strcmp(insan_kahraman.Yavuz_Sultan_Selim.bonus_turu, "saldiri") == 0) {
        suvarinetsaldiri = suvarinetsaldiri * (100 + yavuzbonus)/100;
      } else if (strcmp(insan_kahraman.Yavuz_Sultan_Selim.bonus_turu, "savunma") == 0) {
        suvarinetsavunma = suvarinetsavunma * (100 + yavuzbonus)/100;
      } else if (strcmp(insan_kahraman.Yavuz_Sultan_Selim.bonus_turu, "kritik_sans") == 0) {
          insan_imparatorlugu.suvariler.kritik_sans = insan_imparatorlugu.suvariler.kritik_sans * (100 + yavuzbonus)/100;
    }

    // kusatma
    } else if (strcmp(insan_kahraman.Yavuz_Sultan_Selim.aciklamakahr, "kusatma_makinelerinin") == 0) {
         if (strcmp(insan_kahraman.Yavuz_Sultan_Selim.bonus_turu, "saldiri") == 0) {
        kusatmanetsaldiri = kusatmanetsaldiri * (100 + yavuzbonus)/100;
      } else if (strcmp(insan_kahraman.Yavuz_Sultan_Selim.bonus_turu, "savunma") == 0) {
        kusatmanetsavunma = kusatmanetsaldiri *(100 + yavuzbonus)/100;
      } else if (strcmp(insan_kahraman.Yavuz_Sultan_Selim.bonus_turu, "kritik_sans") == 0) {
          insan_imparatorlugu.kusatma_makineleri.kritik_sans = insan_imparatorlugu.kusatma_makineleri.kritik_sans * (100 + yavuzbonus)/100;
    }
    }
 }


// tugrul
if (strcmp(i_veri.insankahr, "Tugrul_Bey") == 0) {
    // piyade
     if (strcmp(insan_kahraman.Tugrul_Bey.aciklamakahr, "piyadelere") == 0) {
         if (strcmp(insan_kahraman.Tugrul_Bey.bonus_turu, "saldiri") == 0) {
        piyadenetsaldiri = piyadenetsaldiri * (100 + tugrulbonus)/100;
      } else if (strcmp(insan_kahraman.Tugrul_Bey.bonus_turu, "savunma") == 0) {
        piyadenetsavunma=piyadenetsavunma* (100 + tugrulbonus)/100;
      } else if (strcmp(insan_kahraman.Tugrul_Bey.bonus_turu, "kritik_sans") == 0) {
         insan_imparatorlugu.piyadeler.kritik_sans = insan_imparatorlugu.piyadeler.kritik_sans * (100 + tugrulbonus)/100;
    }

    // okcu
    } else if (strcmp(insan_kahraman.Tugrul_Bey.aciklamakahr, "okcularin") == 0) {
         if (strcmp(insan_kahraman.Tugrul_Bey.bonus_turu, "saldiri") == 0) {
        okcunetsaldiri = okcunetsaldiri * (100 + tugrulbonus)/100;
      } else if (strcmp(insan_kahraman.Tugrul_Bey.bonus_turu, "savunma") == 0) {
        okcunetsavunma = okcunetsavunma * (100 + tugrulbonus)/100;
      } else if (strcmp(insan_kahraman.Tugrul_Bey.bonus_turu, "kritik_sans") == 0) {
          insan_imparatorlugu.okcular.kritik_sans = insan_imparatorlugu.okcular.kritik_sans * (100 + tugrulbonus)/100;
    }

    // suvari
    } else if (strcmp(insan_kahraman.Tugrul_Bey.aciklamakahr, "suvarilere") == 0) {
         if (strcmp(insan_kahraman.Tugrul_Bey.bonus_turu, "saldiri") == 0) {
        suvarinetsaldiri = suvarinetsaldiri * (100 + tugrulbonus)/100;
      } else if (strcmp(insan_kahraman.Tugrul_Bey.bonus_turu, "savunma") == 0) {
        suvarinetsavunma = suvarinetsavunma * (100 + tugrulbonus)/100;
      } else if (strcmp(insan_kahraman.Tugrul_Bey.bonus_turu, "kritik_sans") == 0) {
        insan_imparatorlugu.suvariler.kritik_sans = insan_imparatorlugu.suvariler.kritik_sans * (100 + tugrulbonus)/100;
    }

    // kusatma
    } else if (strcmp(insan_kahraman.Tugrul_Bey.aciklamakahr, "kusatma_makinelerinin") == 0) {
         if (strcmp(insan_kahraman.Tugrul_Bey.bonus_turu, "saldiri") == 0) {
        kusatmanetsaldiri = kusatmanetsaldiri * (100 + tugrulbonus)/100;
      } else if (strcmp(insan_kahraman.Tugrul_Bey.bonus_turu, "savunma") == 0) {
        kusatmanetsavunma = kusatmanetsaldiri *(100 + tugrulbonus)/100;
      } else if (strcmp(insan_kahraman.Tugrul_Bey.bonus_turu, "kritik_sans") == 0) {
insan_imparatorlugu.kusatma_makineleri.kritik_sans = insan_imparatorlugu.kusatma_makineleri.kritik_sans * (100 + tugrulbonus)/100;
    }
    }
 }

}
// ork kahraman etkileri uygulama
int d = 1;
if (d == 1) {
    if (strcmp(o_veri.orkkahr, "Goruk_Vahsi") == 0) {
        // orkdovuscu
        if (strcmp(ork_kahraman.Goruk_Vahsi.aciklamakahr, "ork_dovusculerine") == 0) {
            if (strcmp(ork_kahraman.Goruk_Vahsi.bonus_turu, "saldiri") == 0) {
                orkdovuscunetsaldiri = orkdovuscunetsaldiri * (100 + gorukbonus) / 100;
            } else if (strcmp(ork_kahraman.Goruk_Vahsi.bonus_turu, "savunma") == 0) {
                orkdovuscunetsavunma = orkdovuscunetsavunma * (100 + gorukbonus) / 100;
            } else if (strcmp(ork_kahraman.Goruk_Vahsi.bonus_turu, "kritik_sans") == 0) {
            ork_legi.ork_dovusculeri.kritik_sans = ork_legi.ork_dovusculeri.kritik_sans * (100 + gorukbonus)/100;
            }
        } else if (strcmp(ork_kahraman.Goruk_Vahsi.aciklamakahr, "trollerin") == 0) {
            if (strcmp(ork_kahraman.Goruk_Vahsi.bonus_turu, "saldiri") == 0) {
                trolnetsaldiri = trolnetsaldiri * (100 + gorukbonus) / 100;
            } else if (strcmp(ork_kahraman.Goruk_Vahsi.bonus_turu, "savunma") == 0) {
                trolnetsavunma = trolnetsavunma * (100 + gorukbonus) / 100;
            } else if (strcmp(ork_kahraman.Goruk_Vahsi.bonus_turu, "kritik_sans") == 0) {
        ork_legi.troller.kritik_sans = ork_legi.troller.kritik_sans * (100 + gorukbonus)/100;                
            }
        } else if (strcmp(ork_kahraman.Goruk_Vahsi.aciklamakahr, "varg_binicilerine") == 0) {
            if (strcmp(ork_kahraman.Goruk_Vahsi.bonus_turu, "saldiri") == 0) {
                vargnetsaldiri = vargnetsaldiri * (100 + gorukbonus) / 100;
            } else if (strcmp(ork_kahraman.Goruk_Vahsi.bonus_turu, "savunma") == 0) {
                vargnetsavunma = vargnetsavunma * (100 + gorukbonus) / 100;
            } else if (strcmp(ork_kahraman.Goruk_Vahsi.bonus_turu, "kritik_sans") == 0) {
            ork_legi.varg_binicileri.kritik_sans = ork_legi.varg_binicileri.kritik_sans * (100 + gorukbonus)/100;
            }
        } else if (strcmp(ork_kahraman.Goruk_Vahsi.aciklamakahr, "mizrakcilarin") == 0) {
            if (strcmp(ork_kahraman.Goruk_Vahsi.bonus_turu, "saldiri") == 0) {
                mizrakcinetsaldiri = mizrakcinetsaldiri * (100 + gorukbonus) / 100;
            } else if (strcmp(ork_kahraman.Goruk_Vahsi.bonus_turu, "savunma") == 0) {
                mizrakcinetsavunma = mizrakcinetsaldiri * (100 + gorukbonus) / 100;
            } else if (strcmp(ork_kahraman.Goruk_Vahsi.bonus_turu, "kritik_sans") == 0) {
                ork_legi.mizrakcilar.kritik_sans = ork_legi.mizrakcilar.kritik_sans * (100 + gorukbonus)/100;
            }
        }
    }

    if (strcmp(o_veri.orkkahr, "Thruk_Kemikkiran") == 0) {
        // orkdovuscu
        if (strcmp(ork_kahraman.Thruk_Kemikkiran.aciklamakahr, "ork_dovusculerine") == 0) {
            if (strcmp(ork_kahraman.Thruk_Kemikkiran.bonus_turu, "saldiri") == 0) {
                orkdovuscunetsaldiri = orkdovuscunetsaldiri * (100 + thrukbonus) / 100;
            } else if (strcmp(ork_kahraman.Thruk_Kemikkiran.bonus_turu, "savunma") == 0) {
                orkdovuscunetsavunma = orkdovuscunetsavunma * (100 + thrukbonus) / 100;
            } else if (strcmp(ork_kahraman.Thruk_Kemikkiran.bonus_turu, "kritik_sans") == 0) {
                ork_legi.ork_dovusculeri.kritik_sans = ork_legi.ork_dovusculeri.kritik_sans * (100 + thrukbonus)/100;
            }
        } else if (strcmp(ork_kahraman.Thruk_Kemikkiran.aciklamakahr, "trollerin") == 0) {
            if (strcmp(ork_kahraman.Thruk_Kemikkiran.bonus_turu, "saldiri") == 0) {
                trolnetsaldiri = trolnetsaldiri * (100 + thrukbonus) / 100;
            } else if (strcmp(ork_kahraman.Thruk_Kemikkiran.bonus_turu, "savunma") == 0) {
                trolnetsavunma = trolnetsavunma * (100 + thrukbonus) / 100;
            } else if (strcmp(ork_kahraman.Thruk_Kemikkiran.bonus_turu, "kritik_sans") == 0) {
                  ork_legi.troller.kritik_sans = ork_legi.troller.kritik_sans * (100 + thrukbonus)/100;
            }
        } else if (strcmp(ork_kahraman.Thruk_Kemikkiran.aciklamakahr, "varg_binicilerine") == 0) {
            if (strcmp(ork_kahraman.Thruk_Kemikkiran.bonus_turu, "saldiri") == 0) {
                vargnetsaldiri = vargnetsaldiri * (100 + thrukbonus) / 100;
            } else if (strcmp(ork_kahraman.Thruk_Kemikkiran.bonus_turu, "savunma") == 0) {
                vargnetsavunma = vargnetsavunma * (100 + thrukbonus) / 100;
            } else if (strcmp(ork_kahraman.Thruk_Kemikkiran.bonus_turu, "kritik_sans") == 0) {
                  ork_legi.varg_binicileri.kritik_sans = ork_legi.varg_binicileri.kritik_sans * (100 + thrukbonus)/100;
            }
        } else if (strcmp(ork_kahraman.Thruk_Kemikkiran.aciklamakahr, "mizrakcilarin") == 0) {
            if (strcmp(ork_kahraman.Thruk_Kemikkiran.bonus_turu, "saldiri") == 0) {
                mizrakcinetsaldiri = mizrakcinetsaldiri * (100 + thrukbonus) / 100;
            } else if (strcmp(ork_kahraman.Thruk_Kemikkiran.bonus_turu, "savunma") == 0) {
                mizrakcinetsavunma = mizrakcinetsaldiri * (100 + thrukbonus) / 100;
            } else if (strcmp(ork_kahraman.Thruk_Kemikkiran.bonus_turu, "kritik_sans") == 0) {
                  ork_legi.mizrakcilar.kritik_sans = ork_legi.mizrakcilar.kritik_sans * (100 + thrukbonus)/100;
            }
        }
    }

    if (strcmp(o_veri.orkkahr, "Ugar_Zalim") == 0) {
        // orkdovuscu
        if (strcmp(ork_kahraman.Ugar_Zalim.aciklamakahr, "ork_dovusculerine") == 0) {
            if (strcmp(ork_kahraman.Ugar_Zalim.bonus_turu, "saldiri") == 0) {
                orkdovuscunetsaldiri = orkdovuscunetsaldiri * (100 + ugarbonus) / 100;
            } else if (strcmp(ork_kahraman.Ugar_Zalim.bonus_turu, "savunma") == 0) {
                orkdovuscunetsavunma = orkdovuscunetsavunma * (100 + ugarbonus) / 100;
            } else if (strcmp(ork_kahraman.Ugar_Zalim.bonus_turu, "kritik_sans") == 0) {
            ork_legi.ork_dovusculeri.kritik_sans = ork_legi.ork_dovusculeri.kritik_sans * (100 + ugarbonus)/100;
            }
        } else if (strcmp(ork_kahraman.Ugar_Zalim.aciklamakahr, "trollerin") == 0) {
            if (strcmp(ork_kahraman.Ugar_Zalim.bonus_turu, "saldiri") == 0) {
                trolnetsaldiri = trolnetsaldiri * (100 + ugarbonus) / 100;
            } else if (strcmp(ork_kahraman.Ugar_Zalim.bonus_turu, "savunma") == 0) {
                trolnetsavunma = trolnetsavunma * (100 + ugarbonus) / 100;
            } else if (strcmp(ork_kahraman.Ugar_Zalim.bonus_turu, "kritik_sans") == 0) {
             ork_legi.troller.kritik_sans = ork_legi.troller.kritik_sans * (100 + ugarbonus)/100;
            }
        } else if (strcmp(ork_kahraman.Ugar_Zalim.aciklamakahr, "varg_binicilerine") == 0) {
            if (strcmp(ork_kahraman.Ugar_Zalim.bonus_turu, "saldiri") == 0) {
                vargnetsaldiri = vargnetsaldiri * (100 + ugarbonus) / 100;
            } else if (strcmp(ork_kahraman.Ugar_Zalim.bonus_turu, "savunma") == 0) {
                vargnetsavunma = vargnetsavunma * (100 + ugarbonus) / 100;
            } else if (strcmp(ork_kahraman.Ugar_Zalim.bonus_turu, "kritik_sans") == 0) {
                 ork_legi.varg_binicileri.kritik_sans = ork_legi.varg_binicileri.kritik_sans * (100 + ugarbonus)/100;
            }
        } else if (strcmp(ork_kahraman.Ugar_Zalim.aciklamakahr, "mizrakcilarin") == 0) {
            if (strcmp(ork_kahraman.Ugar_Zalim.bonus_turu, "saldiri") == 0) {
                mizrakcinetsaldiri = mizrakcinetsaldiri * (100 + ugarbonus) / 100;
            } else if (strcmp(ork_kahraman.Ugar_Zalim.bonus_turu, "savunma") == 0) {
                mizrakcinetsavunma = mizrakcinetsaldiri * (100 + ugarbonus) / 100;
            } else if (strcmp(ork_kahraman.Ugar_Zalim.bonus_turu, "kritik_sans") == 0) {
                 ork_legi.mizrakcilar.kritik_sans = ork_legi.mizrakcilar.kritik_sans * (100 + ugarbonus)/100;
            }
        }
        else if (strcmp(ork_kahraman.Ugar_Zalim.aciklamakahr, "tum_birimlere") == 0) {
            if (strcmp(ork_kahraman.Ugar_Zalim.bonus_turu, "saldiri") == 0) {
                mizrakcinetsaldiri = mizrakcinetsaldiri * (100 + ugarbonus) / 100;
                orkdovuscunetsaldiri =orkdovuscunetsaldiri * (100 + ugarbonus) / 100;
                vargnetsaldiri = vargnetsaldiri *(100 + ugarbonus) / 100;
                mizrakcinetsaldiri =mizrakcinetsaldiri *(100 + ugarbonus) / 100;
            } else if (strcmp(ork_kahraman.Ugar_Zalim.bonus_turu, "savunma") == 0) {
                mizrakcinetsavunma = mizrakcinetsaldiri * (100 + ugarbonus)/ 100;
                orkdovuscunetsavunma = orkdovuscunetsavunma * (100 + ugarbonus)/100 ;
                vargnetsavunma = vargnetsavunma *(100 + ugarbonus) / 100;
                mizrakcinetsavunma = vargnetsavunma *(100 + ugarbonus) / 100;

            } else if (strcmp(ork_kahraman.Ugar_Zalim.bonus_turu, "kritik_sans") == 0) {
            ork_legi.mizrakcilar.kritik_sans = ork_legi.mizrakcilar.kritik_sans * (100 + ugarbonus)/100;
            ork_legi.troller.kritik_sans = ork_legi.troller.kritik_sans * (100 + ugarbonus)/100;
            ork_legi.varg_binicileri.kritik_sans = ork_legi.varg_binicileri.kritik_sans * (100 + ugarbonus)/100;
            ork_legi.ork_dovusculeri.kritik_sans = ork_legi.ork_dovusculeri.kritik_sans * (100 + ugarbonus)/100;
            }
        }
    }

    if (strcmp(o_veri.orkkahr, "Vrog_Kafakiran") == 0) {
        // orkdovuscu
        if (strcmp(ork_kahraman.Vrog_Kafakiran.aciklamakahr, "ork_dovusculerine") == 0) {
            if (strcmp(ork_kahraman.Vrog_Kafakiran.bonus_turu, "saldiri") == 0) {
                orkdovuscunetsaldiri = orkdovuscunetsaldiri * (100 + vrogbonus) / 100;
            } else if (strcmp(ork_kahraman.Vrog_Kafakiran.bonus_turu, "savunma") == 0) {
                orkdovuscunetsavunma = orkdovuscunetsavunma * (100 + vrogbonus) / 100;
            } else if (strcmp(ork_kahraman.Vrog_Kafakiran.bonus_turu, "kritik_sans") == 0) {
                ork_legi.ork_dovusculeri.kritik_sans = ork_legi.ork_dovusculeri.kritik_sans * (100 + vrogbonus)/100;
            }
        } else if (strcmp(ork_kahraman.Vrog_Kafakiran.aciklamakahr, "trollerin") == 0) {
            if (strcmp(ork_kahraman.Vrog_Kafakiran.bonus_turu, "saldiri") == 0) {
                trolnetsaldiri = trolnetsaldiri * (100 + vrogbonus) / 100;
            } else if (strcmp(ork_kahraman.Vrog_Kafakiran.bonus_turu, "savunma") == 0) {
                trolnetsavunma = trolnetsavunma * (100 + vrogbonus) / 100;
            } else if (strcmp(ork_kahraman.Vrog_Kafakiran.bonus_turu, "kritik_sans") == 0) {
       ork_legi.troller.kritik_sans = ork_legi.troller.kritik_sans * (100 + vrogbonus)/100;
                         
            }
        } else if (strcmp(ork_kahraman.Vrog_Kafakiran.aciklamakahr, "varg_binicilerine") == 0) {
            if (strcmp(ork_kahraman.Vrog_Kafakiran.bonus_turu, "saldiri") == 0) {
                vargnetsaldiri = vargnetsaldiri * (100 + vrogbonus) / 100;
            } else if (strcmp(ork_kahraman.Vrog_Kafakiran.bonus_turu, "savunma") == 0) {
                vargnetsavunma = vargnetsavunma * (100 + vrogbonus) / 100;
            } else if (strcmp(ork_kahraman.Vrog_Kafakiran.bonus_turu, "kritik_sans") == 0) {
            ork_legi.varg_binicileri.kritik_sans = ork_legi.varg_binicileri.kritik_sans * (100 + vrogbonus)/100;
                    
            }
        } else if (strcmp(ork_kahraman.Vrog_Kafakiran.aciklamakahr, "mizrakcilarin") == 0) {
            if (strcmp(ork_kahraman.Vrog_Kafakiran.bonus_turu, "saldiri") == 0) {
                mizrakcinetsaldiri = mizrakcinetsaldiri * (100 + vrogbonus) / 100;
            } else if (strcmp(ork_kahraman.Vrog_Kafakiran.bonus_turu, "savunma") == 0) {
                mizrakcinetsavunma = mizrakcinetsaldiri * (100 + vrogbonus) / 100;
            } else if (strcmp(ork_kahraman.Vrog_Kafakiran.bonus_turu, "kritik_sans") == 0) {
            ork_legi.mizrakcilar.kritik_sans = ork_legi.mizrakcilar.kritik_sans * (100 + vrogbonus)/100;
          
            }
        }
    }
}
// insan canavar etki uygulama
int o=1;
if(o==1){
  // ejder
if (strcmp(i_veri.insancnvr, "Ejderha") == 0)  {
// piyade
     if (strcmp(insan_cnv.Ejderha.aciklamacanv, "piyadelerin") == 0) {
         if (strcmp(insan_cnv.Ejderha.etki_turu, "saldiri") == 0) {
            piyadenetsaldiri = piyadenetsaldiri * (100 + ejderbonus)/100;
         } else if (strcmp(insan_cnv.Ejderha.etki_turu, "savunma") == 0) {
            piyadenetsavunma=piyadenetsavunma* (100 + ejderbonus)/100;
         } else if (strcmp(insan_cnv.Ejderha.etki_turu, "kritik_sans") == 0) {
     insan_imparatorlugu.piyadeler.kritik_sans = insan_imparatorlugu.piyadeler.kritik_sans * (100 + ejderbonus)/100;
         }

// okcu
    } else if (strcmp(insan_cnv.Ejderha.aciklamacanv, "okculara") == 0) {
         if (strcmp(insan_cnv.Ejderha.etki_turu, "saldiri") == 0) {
            okcunetsaldiri = okcunetsaldiri * (100 + ejderbonus)/100;
         } else if (strcmp(insan_cnv.Ejderha.etki_turu, "savunma") == 0) {
            okcunetsavunma = okcunetsavunma * (100 + ejderbonus)/100;
         } else if (strcmp(insan_cnv.Ejderha.etki_turu, "kritik_sans") == 0) {
       insan_imparatorlugu.okcular.kritik_sans = insan_imparatorlugu.okcular.kritik_sans * (100 + ejderbonus)/100;;
         }

// suvari
    } else if (strcmp(insan_cnv.Ejderha.aciklamacanv, "suvarilere") == 0) {
         if (strcmp(insan_cnv.Ejderha.etki_turu, "saldiri") == 0) {
            suvarinetsaldiri = suvarinetsaldiri * (100 + ejderbonus)/100;
         } else if (strcmp(insan_cnv.Ejderha.etki_turu, "savunma") == 0) {
            suvarinetsavunma = suvarinetsavunma * (100 + ejderbonus)/100;
         } else if (strcmp(insan_cnv.Ejderha.etki_turu, "kritik_sans") == 0) {
   insan_imparatorlugu.suvariler.kritik_sans = insan_imparatorlugu.suvariler.kritik_sans * (100 + ejderbonus)/100;;
         }
    } 
 }

// tepegoz
if (strcmp(i_veri.insancnvr, "Tepegoz") == 0) {
// piyade
     if (strcmp(insan_cnv.Tepegoz.aciklamacanv, "piyadelerin") == 0) {
         if (strcmp(insan_cnv.Tepegoz.etki_turu, "saldiri") == 0) {
            piyadenetsaldiri = piyadenetsaldiri * (100 + tepegozbonus)/100;
         } else if (strcmp(insan_cnv.Tepegoz.etki_turu, "savunma") == 0) {
            piyadenetsavunma=piyadenetsavunma* (100 + tepegozbonus)/100;
         } else if (strcmp(insan_cnv.Tepegoz.etki_turu, "kritik_sans") == 0) {
           insan_imparatorlugu.piyadeler.kritik_sans = insan_imparatorlugu.piyadeler.kritik_sans * (100 + tepegozbonus)/100;
         }

// okcu
    } else if (strcmp(insan_cnv.Tepegoz.aciklamacanv, "okcularin") == 0) {
         if (strcmp(insan_cnv.Tepegoz.etki_turu, "saldiri") == 0) {
            okcunetsaldiri = okcunetsaldiri * (100 + tepegozbonus)/100;
         } else if (strcmp(insan_cnv.Tepegoz.etki_turu, "savunma") == 0) {
            okcunetsavunma = okcunetsavunma * (100 + tepegozbonus)/100;
         } else if (strcmp(insan_cnv.Tepegoz.etki_turu, "kritik_sans") == 0) {
      insan_imparatorlugu.okcular.kritik_sans = insan_imparatorlugu.okcular.kritik_sans * (100 + tepegozbonus)/100;
       
         }

// suvari
    } else if (strcmp(insan_cnv.Tepegoz.aciklamacanv, "suvarilere") == 0) {
         if (strcmp(insan_cnv.Tepegoz.etki_turu, "saldiri") == 0) {
            suvarinetsaldiri = suvarinetsaldiri * (100 + tepegozbonus)/100;
         } else if (strcmp(insan_cnv.Tepegoz.etki_turu, "savunma") == 0) {
            suvarinetsavunma = suvarinetsavunma * (100 + tepegozbonus)/100;
         } else if (strcmp(insan_cnv.Tepegoz.etki_turu, "kritik_sans") == 0) {
      insan_imparatorlugu.suvariler.kritik_sans = insan_imparatorlugu.suvariler.kritik_sans * (100 + tepegozbonus)/100;
       
         }
    } 
 }

// agri
if (strcmp(i_veri.insancnvr, "Agri_Dagi_Devleri") == 0) {
// piyade
     if (strcmp(insan_cnv.Agri_Dagi_Devleri.aciklamacanv, "piyadelerin") == 0) {
         if (strcmp(insan_cnv.Agri_Dagi_Devleri.etki_turu, "saldiri") == 0) {
            piyadenetsaldiri = piyadenetsaldiri * (100 + agribonus)/100;
         } else if (strcmp(insan_cnv.Agri_Dagi_Devleri.etki_turu, "savunma") == 0) {
            piyadenetsavunma=piyadenetsavunma* (100 + agribonus)/100;
         } else if (strcmp(insan_cnv.Agri_Dagi_Devleri.etki_turu, "kritik_sans") == 0) {
      insan_imparatorlugu.piyadeler.kritik_sans = insan_imparatorlugu.piyadeler.kritik_sans * (100 + agribonus)/100;
       
         }

// okcu
    } else if (strcmp(insan_cnv.Agri_Dagi_Devleri.aciklamacanv, "okcularin") == 0) {
         if (strcmp(insan_cnv.Agri_Dagi_Devleri.etki_turu, "saldiri") == 0) {
            okcunetsaldiri = okcunetsaldiri * (100 + agribonus)/100;
         } else if (strcmp(insan_cnv.Agri_Dagi_Devleri.etki_turu, "savunma") == 0) {
            okcunetsavunma = okcunetsavunma * (100 + agribonus)/100;
         } else if (strcmp(insan_cnv.Agri_Dagi_Devleri.etki_turu, "kritik_sans") == 0) {
     insan_imparatorlugu.okcular.kritik_sans = insan_imparatorlugu.okcular.kritik_sans * (100 + agribonus)/100;
         }

// suvari
    } else if (strcmp(insan_cnv.Agri_Dagi_Devleri.aciklamacanv, "suvarilere") == 0) {
         if (strcmp(insan_cnv.Agri_Dagi_Devleri.etki_turu, "saldiri") == 0) {
            suvarinetsaldiri = suvarinetsaldiri * (100 + agribonus)/100;
         } else if (strcmp(insan_cnv.Agri_Dagi_Devleri.etki_turu, "savunma") == 0) {
            suvarinetsavunma = suvarinetsavunma * (100 + agribonus)/100;
         } else if (strcmp(insan_cnv.Agri_Dagi_Devleri.etki_turu, "kritik_sans") == 0) {
     insan_imparatorlugu.suvariler.kritik_sans = insan_imparatorlugu.suvariler.kritik_sans * (100 + agribonus)/100;
         }
    } 
 }

// karakurt
if (strcmp(i_veri.insancnvr, "Karakurt") == 0) {
// piyade
     if (strcmp(insan_cnv.Karakurt.aciklamacanv, "piyadelerin") == 0) {
         if (strcmp(insan_cnv.Karakurt.etki_turu, "saldiri") == 0) {
            piyadenetsaldiri = piyadenetsaldiri * (100 + karakurtbonus)/100;
         } else if (strcmp(insan_cnv.Karakurt.etki_turu, "savunma") == 0) {
            piyadenetsavunma=piyadenetsavunma* (100 + karakurtbonus)/100;
         } else if (strcmp(insan_cnv.Karakurt.etki_turu, "kritik_sans") == 0) {
             insan_imparatorlugu.piyadeler.kritik_sans = insan_imparatorlugu.piyadeler.kritik_sans * (100 + karakurtbonus)/100;
         }

// okcu
    } else if (strcmp(insan_cnv.Karakurt.aciklamacanv, "okcularin") == 0) {
         if (strcmp(insan_cnv.Karakurt.etki_turu, "saldiri") == 0) {
            okcunetsaldiri = okcunetsaldiri * (100 + karakurtbonus)/100;
         } else if (strcmp(insan_cnv.Karakurt.etki_turu, "savunma") == 0) {
            okcunetsavunma = okcunetsavunma * (100 + karakurtbonus)/100;
         } else if (strcmp(insan_cnv.Karakurt.etki_turu, "kritik_sans") == 0) {
    insan_imparatorlugu.okcular.kritik_sans = insan_imparatorlugu.okcular.kritik_sans * (100 + karakurtbonus)/100;
         }

// suvari
    } else if (strcmp(insan_cnv.Karakurt.aciklamacanv, "suvarilere") == 0) {
         if (strcmp(insan_cnv.Karakurt.etki_turu, "saldiri") == 0) {
            suvarinetsaldiri = suvarinetsaldiri * (100 + karakurtbonus)/100;
         } else if (strcmp(insan_cnv.Karakurt.etki_turu, "savunma") == 0) {
            suvarinetsavunma = suvarinetsavunma * (100 + karakurtbonus)/100;
         } else if (strcmp(insan_cnv.Karakurt.etki_turu, "kritik_sans") == 0) {
    insan_imparatorlugu.suvariler.kritik_sans = insan_imparatorlugu.suvariler.kritik_sans * (100 + karakurtbonus)/100;
         }
    }
 }

// samur
if (strcmp(i_veri.insancnvr, "Samur") == 0) {
// piyade
     if (strcmp(insan_cnv.Samur.aciklamacanv, "piyadelerin") == 0) {
         if (strcmp(insan_cnv.Samur.etki_turu, "saldiri") == 0) {
            piyadenetsaldiri = piyadenetsaldiri * (100 + samurbonus)/100;
         } else if (strcmp(insan_cnv.Samur.etki_turu, "savunma") == 0) {
            piyadenetsavunma=piyadenetsavunma* (100 + samurbonus)/100;
         } else if (strcmp(insan_cnv.Samur.etki_turu, "kritik_sans") == 0) {
    insan_imparatorlugu.piyadeler.kritik_sans = insan_imparatorlugu.piyadeler.kritik_sans * (100 + samurbonus)/100;
         }

// okcu
    } else if (strcmp(insan_cnv.Samur.aciklamacanv, "okcularin") == 0) {
         if (strcmp(insan_cnv.Samur.etki_turu, "saldiri") == 0) {
            okcunetsaldiri = okcunetsaldiri * (100 + samurbonus)/100;
         } else if (strcmp(insan_cnv.Samur.etki_turu, "savunma") == 0) {
            okcunetsavunma = okcunetsavunma * (100 + samurbonus)/100;
         } else if (strcmp(insan_cnv.Samur.etki_turu, "kritik_sans") == 0) {
    insan_imparatorlugu.okcular.kritik_sans = insan_imparatorlugu.okcular.kritik_sans * (100 + samurbonus)/100;
   
         }

// suvari
    } else if (strcmp(insan_cnv.Samur.aciklamacanv, "suvarilere") == 0) {
         if (strcmp(insan_cnv.Samur.etki_turu, "saldiri") == 0) {
            suvarinetsaldiri = suvarinetsaldiri * (100 + samurbonus)/100;
         } else if (strcmp(insan_cnv.Samur.etki_turu, "savunma") == 0) {
            suvarinetsavunma = suvarinetsavunma * (100 + samurbonus)/100;
         } else if (strcmp(insan_cnv.Samur.etki_turu, "kritik_sans") == 0) {
    insan_imparatorlugu.suvariler.kritik_sans = insan_imparatorlugu.suvariler.kritik_sans * (100 + samurbonus)/100;
   
         }
    }
 }
}
// ork canavar etki uygulama
int f = 1;
if (f == 1) {
    // karatrol
    if (strcmp(o_veri.orkcnvr, "Kara_Troll") == 0) {
        // orkdovuscu
        if (strcmp(ork_cnv.Kara_Troll.aciklamacanv, "ork_dovusculerine") == 0) {
            if (strcmp(ork_cnv.Kara_Troll.etki_turu, "saldiri") == 0) {
                orkdovuscunetsaldiri = orkdovuscunetsaldiri * (100 + karatrolbonus) / 100;
            } else if (strcmp(ork_cnv.Kara_Troll.etki_turu, "savunma") == 0) {
                orkdovuscunetsavunma = orkdovuscunetsavunma * (100 + karatrolbonus) / 100;
            } else if (strcmp(ork_cnv.Kara_Troll.etki_turu, "kritik_sans") == 0) {
            ork_legi.ork_dovusculeri.kritik_sans = ork_legi.ork_dovusculeri.kritik_sans * (100 + karatrolbonus) / 100;
            }
        }

        // trol
        else if (strcmp(ork_cnv.Kara_Troll.aciklamacanv, "trollerin") == 0) {
            if (strcmp(ork_cnv.Kara_Troll.etki_turu, "saldiri") == 0) {
                trolnetsaldiri = trolnetsaldiri * (100 + karatrolbonus) / 100;
            } else if (strcmp(ork_cnv.Kara_Troll.etki_turu, "savunma") == 0) {
                trolnetsavunma = trolnetsavunma * (100 + karatrolbonus) / 100;
            } else if (strcmp(ork_cnv.Kara_Troll.etki_turu, "kritik_sans") == 0) {
         ork_legi.troller.kritik_sans = ork_legi.troller.kritik_sans * (100 + karatrolbonus) / 100;
            }
        }

        // varg
        else if (strcmp(ork_cnv.Kara_Troll.aciklamacanv, "varg_binicilerine") == 0) {
            if (strcmp(ork_cnv.Kara_Troll.etki_turu, "saldiri") == 0) {
                vargnetsaldiri = vargnetsaldiri * (100 + karatrolbonus) / 100;
            } else if (strcmp(ork_cnv.Kara_Troll.etki_turu, "savunma") == 0) {
                vargnetsavunma = vargnetsavunma * (100 + karatrolbonus) / 100;
            } else if (strcmp(ork_cnv.Kara_Troll.etki_turu, "kritik_sans") == 0) {
         ork_legi.varg_binicileri.kritik_sans = ork_legi.varg_binicileri.kritik_sans * (100 + karatrolbonus) / 100;        
            }
        }

        // mizrak
        else if (strcmp(ork_cnv.Kara_Troll.aciklamacanv, "mizrakcilarin") == 0) {
            if (strcmp(ork_cnv.Kara_Troll.etki_turu, "saldiri") == 0) {
                mizrakcinetsaldiri = mizrakcinetsaldiri * (100 + karatrolbonus) / 100;
            } else if (strcmp(ork_cnv.Kara_Troll.etki_turu, "savunma") == 0) {
                mizrakcinetsavunma = mizrakcinetsavunma * (100 + karatrolbonus) / 100;
            } else if (strcmp(ork_cnv.Kara_Troll.etki_turu, "kritik_sans") == 0) {
             ork_legi.mizrakcilar.kritik_sans = ork_legi.mizrakcilar.kritik_sans * (100 + karatrolbonus) / 100;
            }
        }
    }

    // golgekurt
    if (strcmp(o_veri.orkcnvr, "Golge_Kurtlari") == 0) {
        // orkdovuscu
        if (strcmp(ork_cnv.Golge_Kurtlari.aciklamacanv, "ork_dovusculerine") == 0) {
            if (strcmp(ork_cnv.Golge_Kurtlari.etki_turu, "saldiri") == 0) {
                orkdovuscunetsaldiri = orkdovuscunetsaldiri * (100 + golgekurtbonus) / 100;
            } else if (strcmp(ork_cnv.Golge_Kurtlari.etki_turu, "savunma") == 0) {
                orkdovuscunetsavunma = orkdovuscunetsavunma * (100 + golgekurtbonus) / 100;
            } else if (strcmp(ork_cnv.Golge_Kurtlari.etki_turu, "kritik_sans") == 0) {
         ork_legi.ork_dovusculeri.kritik_sans = ork_legi.ork_dovusculeri.kritik_sans * (100 + golgekurtbonus) / 100;
            }
        }

        // trol
        else if (strcmp(ork_cnv.Golge_Kurtlari.aciklamacanv, "trollerin") == 0) {
            if (strcmp(ork_cnv.Golge_Kurtlari.etki_turu, "saldiri") == 0) {
                trolnetsaldiri = trolnetsaldiri * (100 + golgekurtbonus) / 100;
            } else if (strcmp(ork_cnv.Golge_Kurtlari.etki_turu, "savunma") == 0) {
                trolnetsavunma = trolnetsavunma * (100 + golgekurtbonus) / 100;
            } else if (strcmp(ork_cnv.Golge_Kurtlari.etki_turu, "kritik_sans") == 0) {
         ork_legi.troller.kritik_sans = ork_legi.troller.kritik_sans * (100 + golgekurtbonus) / 100;
            }
        }

        // varg
        else if (strcmp(ork_cnv.Golge_Kurtlari.aciklamacanv, "varg_binicilerine") == 0) {
            if (strcmp(ork_cnv.Golge_Kurtlari.etki_turu, "saldiri") == 0) {
                vargnetsaldiri = vargnetsaldiri * (100 + golgekurtbonus) / 100;
            } else if (strcmp(ork_cnv.Golge_Kurtlari.etki_turu, "savunma") == 0) {
                vargnetsavunma = vargnetsavunma * (100 + golgekurtbonus) / 100;
            } else if (strcmp(ork_cnv.Golge_Kurtlari.etki_turu, "kritik_sans") == 0) {
             ork_legi.varg_binicileri.kritik_sans = ork_legi.varg_binicileri.kritik_sans * (100 + golgekurtbonus) / 100;
            }
        }

        // mizrak
        else if (strcmp(ork_cnv.Golge_Kurtlari.aciklamacanv, "mizrakcilarin") == 0) {
            if (strcmp(ork_cnv.Golge_Kurtlari.etki_turu, "saldiri") == 0) {
                mizrakcinetsaldiri = mizrakcinetsaldiri * (100 + golgekurtbonus) / 100;
            } else if (strcmp(ork_cnv.Golge_Kurtlari.etki_turu, "savunma") == 0) {
                mizrakcinetsavunma = mizrakcinetsavunma * (100 + golgekurtbonus) / 100;
            } else if (strcmp(ork_cnv.Golge_Kurtlari.etki_turu, "kritik_sans") == 0) {
             ork_legi.mizrakcilar.kritik_sans = ork_legi.mizrakcilar.kritik_sans * (100 + golgekurtbonus) / 100;
            }
        }
    }

    // camur
    if (strcmp(o_veri.orkcnvr, "Camur_Devleri") == 0) {
        // orkdovuscu
        if (strcmp(ork_cnv.Camur_Devleri.aciklamacanv, "ork_dovusculerine") == 0) {
            if (strcmp(ork_cnv.Camur_Devleri.etki_turu, "saldiri") == 0) {
                orkdovuscunetsaldiri = orkdovuscunetsaldiri * (100 + camurbonus) / 100;
            } else if (strcmp(ork_cnv.Camur_Devleri.etki_turu, "savunma") == 0) {
                orkdovuscunetsavunma = orkdovuscunetsavunma * (100 + camurbonus) / 100;
            } else if (strcmp(ork_cnv.Camur_Devleri.etki_turu, "kritik_sans") == 0) {
         ork_legi.ork_dovusculeri.kritik_sans = ork_legi.ork_dovusculeri.kritik_sans * (100 + camurbonus) / 100;
            }
        }

        // trol
        else if (strcmp(ork_cnv.Camur_Devleri.aciklamacanv, "trollerin") == 0) {
            if (strcmp(ork_cnv.Camur_Devleri.etki_turu, "saldiri") == 0) {
                trolnetsaldiri = trolnetsaldiri * (100 + camurbonus) / 100;
            } else if (strcmp(ork_cnv.Camur_Devleri.etki_turu, "savunma") == 0) {
                trolnetsavunma = trolnetsavunma * (100 + camurbonus) / 100;
            } else if (strcmp(ork_cnv.Camur_Devleri.etki_turu, "kritik_sans") == 0) {
                ork_legi.troller.kritik_sans = ork_legi.troller.kritik_sans * (100 + camurbonus) / 100;                
            }
        }

        // varg
        else if (strcmp(ork_cnv.Camur_Devleri.aciklamacanv, "varg_binicilerine") == 0) {
            if (strcmp(ork_cnv.Camur_Devleri.etki_turu, "saldiri") == 0) {
                vargnetsaldiri = vargnetsaldiri * (100 + camurbonus) / 100;
            } else if (strcmp(ork_cnv.Camur_Devleri.etki_turu, "savunma") == 0) {
                vargnetsavunma = vargnetsavunma * (100 + camurbonus) / 100;
            } else if (strcmp(ork_cnv.Camur_Devleri.etki_turu, "kritik_sans") == 0) {
                ork_legi.varg_binicileri.kritik_sans = ork_legi.varg_binicileri.kritik_sans * (100 + camurbonus) / 100;
            }
        }

        // mizrak
        else if (strcmp(ork_cnv.Camur_Devleri.aciklamacanv, "mizrakcilarin") == 0) {
            if (strcmp(ork_cnv.Camur_Devleri.etki_turu, "saldiri") == 0) {
                mizrakcinetsaldiri = mizrakcinetsaldiri * (100 + camurbonus) / 100;
            } else if (strcmp(ork_cnv.Camur_Devleri.etki_turu, "savunma") == 0) {
                mizrakcinetsavunma = mizrakcinetsavunma * (100 + camurbonus) / 100;
            } else if (strcmp(ork_cnv.Camur_Devleri.etki_turu, "kritik_sans") == 0) {
            ork_legi.mizrakcilar.kritik_sans = ork_legi.mizrakcilar.kritik_sans * (100 + camurbonus) / 100;
            }
        }
    }
}
// insanda arastirma etkileri
int g=1;
if(g == 1){
//savunma
if ( i_veri.savunma_ustaligi>0) {
// 1
     if (i_veri.savunma_ustaligi==1) {
         piyadenetsavunma = piyadenetsavunma * (100 + savunmaarastirma1)/100;
         okcunetsavunma = okcunetsavunma * (100 + savunmaarastirma1)/100;
         suvarinetsavunma = suvarinetsavunma * (100 + savunmaarastirma1)/100;
         kusatmanetsavunma = kusatmanetsavunma * (100 + savunmaarastirma1)/100;
    } 
    // 2
    else if (i_veri.savunma_ustaligi==2) {
        piyadenetsavunma = piyadenetsavunma * (100 + savunmaarastirma2)/100;
         okcunetsavunma = okcunetsavunma * (100 + savunmaarastirma2)/100;
         suvarinetsavunma = suvarinetsavunma * (100 + savunmaarastirma2)/100;
         kusatmanetsavunma = kusatmanetsavunma * (100 + savunmaarastirma2)/100;

    } 
    // 3
    else if (i_veri.savunma_ustaligi==3) {
        piyadenetsavunma = piyadenetsavunma * (100 + savunmaarastirma3)/100;
         okcunetsavunma = okcunetsavunma * (100 + savunmaarastirma3)/100;
         suvarinetsavunma = suvarinetsavunma * (100 + savunmaarastirma3)/100;
         kusatmanetsavunma = kusatmanetsavunma * (100 + savunmaarastirma3)/100;
    }}
// saldiri
if (i_veri.saldiri_gelistirmesi>0) {
// 1
     if (i_veri.saldiri_gelistirmesi==1) {
        piyadenetsaldiri = piyadenetsaldiri * (100 + saldiriarastirma1)/100;
         okcunetsaldiri = okcunetsaldiri * (100 + saldiriarastirma1)/100;
         suvarinetsaldiri = suvarinetsaldiri * (100 + saldiriarastirma1)/100;
         kusatmanetsaldiri = kusatmanetsaldiri * (100 + saldiriarastirma1)/100;
    } 
    // 2
    else if (i_veri.saldiri_gelistirmesi==2) {
         piyadenetsaldiri = piyadenetsaldiri * (100 + saldiriarastirma2)/100;
         okcunetsaldiri = okcunetsaldiri * (100 + saldiriarastirma2)/100;
         suvarinetsaldiri = suvarinetsaldiri * (100 + saldiriarastirma2)/100;
         kusatmanetsaldiri = kusatmanetsaldiri * (100 + saldiriarastirma2)/100;
    } 
    // 3
    else if (i_veri.saldiri_gelistirmesi==3) {
         piyadenetsaldiri = piyadenetsaldiri * (100 + saldiriarastirma3)/100;
         okcunetsaldiri = okcunetsaldiri * (100 + saldiriarastirma3)/100;
         suvarinetsaldiri = suvarinetsaldiri * (100 + saldiriarastirma3)/100;
         kusatmanetsaldiri = kusatmanetsaldiri * (100 + saldiriarastirma3)/100;
    }}
// kusatma
if (i_veri.kusatma_ustaligi>0) {
// 1
     if (i_veri.kusatma_ustaligi==1) {
         kusatmanetsaldiri = kusatmanetsaldiri * (100 + saldiriarastirma1)/100;
    } 
    // 2
    else if (i_veri.kusatma_ustaligi==2) {
         kusatmanetsaldiri = kusatmanetsaldiri * (100 + saldiriarastirma2)/100;
    } 
    // 3
    else if (i_veri.kusatma_ustaligi==3) {
         kusatmanetsaldiri = kusatmanetsaldiri * (100 + saldiriarastirma2)/100;
    }}
// egitim
if (i_veri.elit_egitim>0) {

// 1
     if (i_veri.elit_egitim==1) {
     
    insan_imparatorlugu.piyadeler.kritik_sans = insan_imparatorlugu.piyadeler.kritik_sans * (100 + elitegitim1) / 100;
           insan_imparatorlugu.suvariler.kritik_sans = insan_imparatorlugu.suvariler.kritik_sans * (100 + elitegitim1) / 100;
        insan_imparatorlugu.okcular.kritik_sans = insan_imparatorlugu.okcular.kritik_sans * (100 + elitegitim1) / 100;
        insan_imparatorlugu.kusatma_makineleri.kritik_sans = insan_imparatorlugu.kusatma_makineleri.kritik_sans * (100 + elitegitim1) / 100;
    } 
        
    // 2
    else if (i_veri.elit_egitim==2) {
      
            insan_imparatorlugu.piyadeler.kritik_sans = insan_imparatorlugu.piyadeler.kritik_sans * (100 + elitegitim2) / 100;
           insan_imparatorlugu.suvariler.kritik_sans = insan_imparatorlugu.suvariler.kritik_sans * (100 + elitegitim2) / 100;
        insan_imparatorlugu.okcular.kritik_sans = insan_imparatorlugu.okcular.kritik_sans * (100 + elitegitim2) / 100;
        insan_imparatorlugu.kusatma_makineleri.kritik_sans = insan_imparatorlugu.kusatma_makineleri.kritik_sans * (100 + elitegitim2) / 100;
        } 
    
    // 3
    else if (i_veri.elit_egitim==3) {
   
            insan_imparatorlugu.piyadeler.kritik_sans = insan_imparatorlugu.piyadeler.kritik_sans * (100 + elitegitim3) / 100;
           insan_imparatorlugu.suvariler.kritik_sans = insan_imparatorlugu.suvariler.kritik_sans * (100 + elitegitim3) / 100;
        insan_imparatorlugu.okcular.kritik_sans = insan_imparatorlugu.okcular.kritik_sans * (100 + elitegitim3) / 100;
        insan_imparatorlugu.kusatma_makineleri.kritik_sans = insan_imparatorlugu.kusatma_makineleri.kritik_sans * (100 + elitegitim3) / 100;
       
    }}}
// orkta arastirma etkileri
int h=1;
if(h == 1){
//savunma
if ( o_veri.savunma_ustaligi>0) {
// 1
     if (o_veri.savunma_ustaligi==1) {
         orkdovuscunetsavunma = orkdovuscunetsavunma * (100 + savunmaarastirma1)/100;
         vargnetsavunma = vargnetsavunma * (100 + savunmaarastirma1)/100;
         trolnetsavunma = trolnetsavunma * (100 + savunmaarastirma1)/100;
         mizrakcinetsavunma = mizrakcinetsavunma * (100 + savunmaarastirma1)/100;
    } 
    // 2
    else if (o_veri.savunma_ustaligi==2) {
        orkdovuscunetsavunma = orkdovuscunetsavunma * (100 + savunmaarastirma2)/100;
         vargnetsavunma = vargnetsavunma * (100 + savunmaarastirma2)/100;
         trolnetsavunma = trolnetsavunma * (100 + savunmaarastirma2)/100;
         mizrakcinetsavunma = mizrakcinetsavunma * (100 + savunmaarastirma2)/100;

    } 
    // 3
    else if (o_veri.savunma_ustaligi==3) {
        orkdovuscunetsavunma = orkdovuscunetsavunma * (100 + savunmaarastirma3)/100;
         vargnetsavunma = vargnetsavunma * (100 + savunmaarastirma3)/100;
         trolnetsavunma = trolnetsavunma * (100 + savunmaarastirma3)/100;
         mizrakcinetsavunma = mizrakcinetsavunma * (100 + savunmaarastirma3)/100;
    } 
 }

// saldiri
if (o_veri.saldiri_gelistirmesi>0) {
// 1
     if (o_veri.saldiri_gelistirmesi==1) {
        orkdovuscunetsaldiri = orkdovuscunetsaldiri * (100 + saldiriarastirma1)/100;
         vargnetsaldiri = vargnetsaldiri * (100 + saldiriarastirma1)/100;
         trolnetsaldiri = trolnetsaldiri * (100 + saldiriarastirma1)/100;
         mizrakcinetsaldiri = mizrakcinetsaldiri * (100 + saldiriarastirma1)/100;
         

    } 
    // 2
    else if (o_veri.saldiri_gelistirmesi==2) {
         orkdovuscunetsaldiri = orkdovuscunetsaldiri * (100 + saldiriarastirma2)/100;
         vargnetsaldiri = vargnetsaldiri * (100 + saldiriarastirma2)/100;
         trolnetsaldiri = trolnetsaldiri * (100 + saldiriarastirma2)/100;
         mizrakcinetsaldiri = mizrakcinetsaldiri * (100 + saldiriarastirma2)/100;

    } 
    // 3
    else if (o_veri.saldiri_gelistirmesi==3) {
         orkdovuscunetsaldiri = orkdovuscunetsaldiri * (100 + saldiriarastirma3)/100;
         vargnetsaldiri = vargnetsaldiri * (100 + saldiriarastirma3)/100;
         trolnetsaldiri = trolnetsaldiri * (100 + saldiriarastirma3)/100;
         mizrakcinetsaldiri = mizrakcinetsaldiri * (100 + saldiriarastirma3)/100;
    } 
 }


// egitim
if (o_veri.elit_egitim>0) {
// 1
     if (o_veri.elit_egitim==1) {
         ork_legi.ork_dovusculeri.kritik_sans = ork_legi.ork_dovusculeri.kritik_sans * (100 + elitegitim1) / 100;
         ork_legi.troller.kritik_sans = ork_legi.troller.kritik_sans * (100 + elitegitim1) / 100;
         ork_legi.mizrakcilar.kritik_sans = ork_legi.mizrakcilar.kritik_sans * (100 + elitegitim1) / 100;
          ork_legi.varg_binicileri.kritik_sans = ork_legi.mizrakcilar.kritik_sans * (100 + elitegitim1) / 100;

    } 
    // 2
    else if (o_veri.elit_egitim==2) {
             ork_legi.ork_dovusculeri.kritik_sans = ork_legi.ork_dovusculeri.kritik_sans * (100 + elitegitim2) / 100;
         ork_legi.troller.kritik_sans = ork_legi.troller.kritik_sans * (100 + elitegitim2) / 100;
         ork_legi.mizrakcilar.kritik_sans = ork_legi.mizrakcilar.kritik_sans * (100 + elitegitim2) / 100;
          ork_legi.varg_binicileri.kritik_sans = ork_legi.mizrakcilar.kritik_sans * (100 + elitegitim2) / 100;


    } 
    // 3
    else if (o_veri.elit_egitim==3) {
             ork_legi.ork_dovusculeri.kritik_sans = ork_legi.ork_dovusculeri.kritik_sans * (100 + elitegitim3) / 100;
         ork_legi.troller.kritik_sans = ork_legi.troller.kritik_sans * (100 + elitegitim3) / 100;
         ork_legi.mizrakcilar.kritik_sans = ork_legi.mizrakcilar.kritik_sans * (100 + elitegitim3) / 100;
          ork_legi.varg_binicileri.kritik_sans = ork_legi.mizrakcilar.kritik_sans * (100 + elitegitim3) / 100;

    } 
 }



}
      
    

float insantotalhasar = piyadenetsaldiri + okcunetsaldiri + suvarinetsaldiri + kusatmanetsaldiri;
float orktotalhasar = orkdovuscunetsaldiri + mizrakcinetsaldiri + vargnetsaldiri + trolnetsaldiri;

float insantotalsavunma =piyadenetsavunma + okcunetsavunma + suvarinetsavunma + kusatmanetsavunma;
float orktotalsavunma = orkdovuscunetsavunma + mizrakcinetsavunma + vargnetsavunma + trolnetsavunma;

float insantotalcan =piyadenetsaglik + okcunetsaglik +suvarinetsaglik + kusatmanetsaglik;
float orktotalcan =orkdovuscunetsaglik + mizrakcinetsaglik + vargnetsaglik + trolnetsaglik;

float insantotalbirimsayisi = birim1.insanbirimler.piyadesayisi + birim1.insanbirimler.okcusayisi + birim1.insanbirimler.kusatmacisayisi + birim1.insanbirimler.suvarisayisi;
float orktotalbirimsayisi = birim2.orkbirimler.orkdovuscusayisi + birim2.orkbirimler.mizrakcisayisi + birim2.orkbirimler.vargsayisi + birim2.orkbirimler.trolsayisi;

      int pktur = floor(100/insan_imparatorlugu.piyadeler.kritik_sans);
      int oktur = floor(100/insan_imparatorlugu.okcular.kritik_sans);
      int sktur = floor(100/insan_imparatorlugu.suvariler.kritik_sans);
      int orkktur = floor(100/ork_legi.ork_dovusculeri.kritik_sans);
      int tktur = floor(100/ork_legi.troller.kritik_sans);
      int vktur = floor(100/ork_legi.varg_binicileri.kritik_sans);
      int mktur = floor(100/ork_legi.mizrakcilar.kritik_sans);








////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 
SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // SDL ve bileşenlerini başlat
    if (init(&window, &renderer) != 0) {
        return -1;
    }

    // Font yükleme
    TTF_Font* font = loadFont("C:/Users/minth/Documents/VSCODE/SDL2_ttf-2.22.0-win32-x64/arial.ttf", 18);
    if (font == NULL) {
        cleanup(renderer, window, font);
        return -1;
    }

    // Birimleri yükle

    if (loadUnits(renderer, &birim1,&birim2,insan_imparatorlugu.piyadeler.saglik,insan_imparatorlugu.okcular.saglik,insan_imparatorlugu.suvariler.saglik,insan_imparatorlugu.kusatma_makineleri.saglik,ork_legi.ork_dovusculeri.saglik,ork_legi.mizrakcilar.saglik,ork_legi.troller.saglik,ork_legi.varg_binicileri.saglik)!= 0) {
        cleanup(renderer, window, font);
        return -1;
    }

    // Ekranı çiz
    drawGrid(renderer, font);

    // Ekranı güncelle
    SDL_RenderPresent(renderer);

    // Event döngüsü
    // Event döngüsü
// Event döngüsü
// Event döngüsü
SDL_Event e;
int quit = 0;
while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = 1;
        }
    }
}

// Kaynakları temizle

    // Fontu serbest bırak
    if (font) {
        TTF_CloseFont(font);
        font = NULL;
    }

    // Renderer'ı serbest bırak
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    // Penceriyi serbest bırak
    if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    // SDL_ttf'yi kapat
    TTF_Quit();

    // SDL'yi kapat
    SDL_Quit();





// Terminalde çıktıyı görmek için bekle

fflush(stdout);


printf("devam etmek icin bir tusa basin:");
// Kullanıcı bir tuşa basana kadar bekle
getchar();


FILE *savas_sim = fopen("C:\\users\\minth\\Documents\\VSCODE\\savas_sim.txt", "wb");
 

for(int tursayisi = 1;(birim2.orkbirimler.orkdovuscusayisi > 0 || birim2.orkbirimler.mizrakcisayisi > 0 || birim2.orkbirimler.vargsayisi > 0 || birim2.orkbirimler.trolsayisi > 0) &&
       (birim1.insanbirimler.piyadesayisi > 0 || birim1.insanbirimler.okcusayisi > 0 || birim1.insanbirimler.kusatmacisayisi > 0 || birim1.insanbirimler.suvarisayisi > 0)
; tursayisi++)
{   

if(tursayisi % 5 == 0)// yorgunluk
{


    piyadenetsaldiri = piyadenetsaldiri * 0.9;
 piyadenetsavunma = piyadenetsavunma * 0.9;
okcunetsaldiri = okcunetsaldiri * 0.9;
okcunetsavunma = okcunetsavunma * 0.9;
 suvarinetsaldiri = suvarinetsaldiri * 0.9;
suvarinetsavunma = suvarinetsavunma * 0.9;
kusatmanetsaldiri = kusatmanetsaldiri * 0.9;
kusatmanetsavunma = kusatmanetsavunma * 0.9;
orkdovuscunetsaldiri = orkdovuscunetsaldiri * 0.9;
orkdovuscunetsavunma = orkdovuscunetsavunma * 0.9;
mizrakcinetsaldiri = mizrakcinetsaldiri * 0.9;
 mizrakcinetsavunma = mizrakcinetsavunma * 0.9;
 vargnetsaldiri = vargnetsaldiri * 0.9;
 vargnetsavunma = vargnetsavunma * 0.9;
 trolnetsaldiri = trolnetsaldiri * 0.9;
trolnetsavunma = trolnetsavunma * 0.9;
}
 

    if(tursayisi%2 == 1) //insan turu
    {
        if(tursayisi % pktur == 0)
        {
          
            float piyadekritikdamage = piyadenetsaldiri;
            insantotalhasar = insantotalhasar + piyadekritikdamage;
        }   
        if(tursayisi % oktur == 0)
        { 
            float okcukritikdamage = okcunetsaldiri;
            insantotalhasar = insantotalhasar + okcukritikdamage;
        }
        if(tursayisi % sktur== 0)
        {
            
            float suvarikritikdamage = suvarinetsaldiri;
            insantotalhasar = insantotalhasar + suvarikritikdamage;
        }

     

        float insannethasar = insantotalhasar *  (1 -  (orktotalsavunma/insantotalhasar)) ; 
        if((orktotalsavunma/insantotalhasar) > 1)
        {
            insannethasar = 0;
        }
        else{



        float orkadusen = insannethasar * (orkdovuscunetsavunma/orktotalsavunma);
        float mizrakcidusen = insannethasar * (mizrakcinetsavunma/orktotalsavunma);
        float vargdusen = insannethasar * (vargnetsavunma/orktotalsavunma);
        float troldusen = insannethasar * (trolnetsavunma/orktotalsavunma); 

        orkdovuscunetsaglik = floor(orkdovuscunetsaglik - orkadusen);
        mizrakcinetsaglik = floor (mizrakcinetsaglik - mizrakcidusen);
        vargnetsaglik = floor(vargnetsaglik - vargdusen);
        trolnetsaglik = floor(trolnetsaglik - troldusen);

        ork_legi.ork_dovusculeri.saglik = orkdovuscunetsaglik/birim2.orkbirimler.orkdovuscusayisi;
        ork_legi.varg_binicileri.saglik = vargnetsaglik/birim2.orkbirimler.vargsayisi;
        ork_legi.mizrakcilar.saglik = mizrakcinetsaglik/birim2.orkbirimler.mizrakcisayisi;
        ork_legi.troller.saglik = trolnetsaglik/birim2.orkbirimler.trolsayisi;

if (ork_legi.ork_dovusculeri.saglik < 0) {
    birim2.orkbirimler.orkdovuscusayisi = 0;
    ork_legi.ork_dovusculeri.saglik = 0;
}
if (ork_legi.mizrakcilar.saglik< 0) {
    birim2.orkbirimler.mizrakcisayisi = 0;
    ork_legi.mizrakcilar.saglik = 0;
}


if (ork_legi.troller.saglik < 0) {
    birim2.orkbirimler.trolsayisi = 0;
    ork_legi.troller.saglik = 0;
}
if (ork_legi.varg_binicileri.saglik < 0) {
    birim2.orkbirimler.vargsayisi = 0;
    ork_legi.varg_binicileri.saglik = 0;
}


 orktotalbirimsayisi = birim2.orkbirimler.orkdovuscusayisi + birim2.orkbirimler.mizrakcisayisi + birim2.orkbirimler.vargsayisi + birim2.orkbirimler.trolsayisi;
orktotalcan =orkdovuscunetsaglik + mizrakcinetsaglik + vargnetsaglik + trolnetsaglik;
fprintf(savas_sim,"\n\n%d.TUR: INSAN ORDUSU SALDIRIR.\nORK DOVUSCULERINE VERILEN HASAR :%.2f\nMIZRAKCILARA VERILEN HASAR :%.2f\nVARG BINICILERINE VERILEN HASAR :%.2f\nTROLLERE VERILEN HASAR :%.2f\n",tursayisi,orkadusen,mizrakcidusen,vargdusen,troldusen);

}


   
if(birim2.orkbirimler.orkdovuscusayisi <= 0 && birim2.orkbirimler.mizrakcisayisi <= 0 && birim2.orkbirimler.vargsayisi <= 0 && birim2.orkbirimler.trolsayisi <=0 )
    {   
        

      fprintf (savas_sim,"\n\nBUTUN ORK ORDUSU OLDU. INSANLAR KAZANDI");  
     
           break;}
    }
 if(tursayisi %2 ==0) //ork turu
    {

    if(tursayisi % orkktur  ==0)
        { 
            float orkdovkritikdamage = orkdovuscunetsaldiri;
            orktotalhasar = orktotalhasar + orkdovkritikdamage;
        }
     if(tursayisi % mktur== 0)
        {  
            float mizrakcikritikdamage = mizrakcinetsaldiri;
            orktotalhasar = orktotalhasar + mizrakcikritikdamage;
        } 
         if(tursayisi % tktur == 0)
        {  ;
            float trolkritikdamage = trolnetsaldiri;
            orktotalhasar = orktotalhasar + trolkritikdamage;
        }  
        if(tursayisi % vktur== 0)
        {  
            float vargkritikdamage = vargnetsaldiri;
            orktotalhasar = orktotalhasar + vargkritikdamage;
        }

        float orknethasar = orktotalhasar * (1 - (insantotalsavunma/orktotalhasar));

    if((insantotalsavunma/orktotalhasar)>1)
    {
        orknethasar = 0;
    }
    else{   
         float piyadedusen = orknethasar * (piyadenetsavunma/insantotalsavunma);
        float okcudusen = orknethasar * (okcunetsavunma/insantotalsavunma);
        float suvaridusen = orknethasar * (suvarinetsavunma/insantotalsavunma);
        float kusatmadusen = orknethasar * (kusatmanetsavunma/insantotalsavunma); 

     
       piyadenetsaglik = floor(piyadenetsaglik - piyadedusen);
        okcunetsaglik = floor (okcunetsaglik - okcudusen);
        suvarinetsaglik = floor(suvarinetsaglik - suvaridusen);
        kusatmanetsaglik = floor(kusatmanetsaglik - kusatmadusen);
         
         insan_imparatorlugu.piyadeler.saglik = piyadenetsaglik/birim1.insanbirimler.piyadesayisi;
insan_imparatorlugu.okcular.saglik =okcunetsaglik/birim1.insanbirimler.okcusayisi;
insan_imparatorlugu.suvariler.saglik = suvarinetsaglik/birim1.insanbirimler.suvarisayisi;
insan_imparatorlugu.kusatma_makineleri.saglik = kusatmanetsaglik/birim1.insanbirimler.kusatmacisayisi;
        

if (insan_imparatorlugu.piyadeler.saglik < 0) {
    birim1.insanbirimler.piyadesayisi = 0;
    insan_imparatorlugu.piyadeler.saglik = 0;

}

if (insan_imparatorlugu.okcular.saglik  < 0) {
    birim1.insanbirimler.okcusayisi = 0;
    insan_imparatorlugu.okcular.saglik = 0;
}

if (insan_imparatorlugu.suvariler.saglik < 0) {
    birim1.insanbirimler.suvarisayisi = 0;
    insan_imparatorlugu.suvariler.saglik = 0;
}

if (insan_imparatorlugu.kusatma_makineleri.saglik < 0) {
    birim1.insanbirimler.kusatmacisayisi = 0;
    insan_imparatorlugu.kusatma_makineleri.saglik = 0;
}


insantotalbirimsayisi = birim1.insanbirimler.piyadesayisi + birim1.insanbirimler.okcusayisi + birim1.insanbirimler.kusatmacisayisi + birim1.insanbirimler.suvarisayisi;

insantotalcan =piyadenetsaglik + okcunetsaglik +suvarinetsaglik + kusatmanetsaglik;
fprintf(savas_sim,"\n\n%d.TUR: ORK ORDUSU SALDIRIR.\nPIYADELERE VERILEN HASAR :%.2f\nOKCULARA VERILEN HASAR :%.2f\nSUVARILERE VERILEN HASAR :%.2f\nKUSATMA MAKINELERINE VERILEN HASAR :%.2f\n ",tursayisi,piyadedusen,okcudusen,suvaridusen,kusatmadusen);

}
       
      


if(birim1.insanbirimler.piyadesayisi <= 0 && birim1.insanbirimler.okcusayisi <= 0 &&  birim1.insanbirimler.kusatmacisayisi <= 0 &&  birim1.insanbirimler.suvarisayisi <=0 )
    {

   
     fprintf(savas_sim,"\n\nBUTUN INSAN ORDUSU OLDU. ORKLAR KAZANDI:");
   
           break;}

    }

}
 



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  SDL_Window* window2 = NULL;
    SDL_Renderer* renderer2 = NULL;

    // SDL ve bileşenlerini başlat
    if (init(&window2, &renderer2) != 0) {
        return -1;
    }

    // Font yükleme
    TTF_Font* font2 = loadFont("C:/Users/minth/Documents/VSCODE/SDL2_ttf-2.22.0-win32-x64/arial.ttf", 18);
    if (font2 == NULL) {
        cleanup(renderer2, window2, font2);
        return -1;
    }
// Birimleri yükle
    if (loadUnits2(renderer2, &birim1,&birim2,insan_imparatorlugu.piyadeler.saglik,insan_imparatorlugu.okcular.saglik,insan_imparatorlugu.suvariler.saglik,insan_imparatorlugu.kusatma_makineleri.saglik,ork_legi.ork_dovusculeri.saglik,ork_legi.mizrakcilar.saglik,ork_legi.troller.saglik,ork_legi.varg_binicileri.saglik)!= 0) {
        cleanup(renderer2, window2, font2);
        return -1;
    }

    // Ekranı çiz
    drawGrid2(renderer2, font2);

    // Ekranı güncelle
    SDL_RenderPresent(renderer2);

SDL_Event k;
quit = 0;
while (!quit) {
    while (SDL_PollEvent(&k) != 0) {
        if (k.type == SDL_QUIT) {
            quit = 1;
        }
    }
}

// Kaynakları temizle
cleanup(renderer2, window2, font2);

// Terminalde çıktıyı görmek için bekle

fflush(stdout);


  return 0;
    }