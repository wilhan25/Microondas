#pragma once
#include <Arduino.h>

// ════════════════════════════════════════════════
//   ENUM — nomes dos botões
// ════════════════════════════════════════════════
typedef enum {
    BTN_POWER = 0,
    BTN_MENU,
    BTN_TEST,
    BTN_PLUS,
    BTN_SETA,
    BTN_PREV,
    BTN_PLAY,
    BTN_NEXT,
    BTN_0,
    BTN_MINUS,
    BTN_C,
    BTN_1, BTN_2, BTN_3,
    BTN_4, BTN_5, BTN_6,
    BTN_7, BTN_8, BTN_9,
    BTN_UNKNOWN
} botoes_controle;

// ════════════════════════════════════════════════
//   TABELA DE MAPEAMENTO
//   Altere apenas aqui para adaptar a outro controle
// ════════════════════════════════════════════════
typedef struct {
    uint32_t        codigo;
    botoes_controle botao;
} mapeamento_t;

static const mapeamento_t mapa_controle[] = {
    { 0xFFA25D, BTN_POWER },
    { 0xFFE21D, BTN_MENU  },
    { 0xFF22DD, BTN_TEST  },
    { 0xFF02FD, BTN_PLUS  },
    { 0xFFC23D, BTN_SETA  },
    { 0xFFE01F, BTN_PREV  },
    { 0xFFA857, BTN_PLAY  },
    { 0xFF906F, BTN_NEXT  },
    { 0xFF6897, BTN_0     },
    { 0xFF9867, BTN_MINUS },
    { 0xFFB04F, BTN_C     },
    { 0xFF30CF, BTN_1     },
    { 0xFF18E7, BTN_2     },
    { 0xFF7A85, BTN_3     },
    { 0xFF10EF, BTN_4     },
    { 0xFF38C7, BTN_5     },
    { 0xFF5AA5, BTN_6     },
    { 0xFF42BD, BTN_7     },
    { 0xFF4AB5, BTN_8     },
    { 0xFF52AD, BTN_9     },
};

static const size_t mapa_len = sizeof(mapa_controle) / sizeof(mapa_controle[0]);

static const char* const nomes_botoes[] = {
    "POWER", "MENU", "TEST", "PLUS", "SETA",
    "PREV",  "PLAY", "NEXT", "0",    "MINUS",
    "C",     "1",    "2",    "3",    "4",
    "5",     "6",    "7",    "8",    "9",
    "UNKNOWN"
};

// converte raw code no enum correspondente
static inline botoes_controle conversaoBtn(uint32_t raw) {
    for (size_t i = 0; i < mapa_len; i++) {
        if (mapa_controle[i].codigo == raw)
            return mapa_controle[i].botao;
    }
    return BTN_UNKNOWN;
}

// retorna o nome do botão em texto (para debug)
static inline const char* nomeBtn(botoes_controle btn) {
    if (btn >= BTN_UNKNOWN) return nomes_botoes[BTN_UNKNOWN];
    return nomes_botoes[btn];
}
