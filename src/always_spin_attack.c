#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

PlayState* gPlay;

RECOMP_HOOK("Message_DrawTextNES") void Message_DrawTextNES_Hook(PlayState* play, Gfx** gfxP, u16 textDrawPos) {
    gPlay = play;
}

RECOMP_HOOK_RETURN("Message_DrawTextNES") void Message_DrawTextNES_Return() {
    MessageContext* msgCtx = &gPlay->msgCtx;

    if (msgCtx->textDelayTimer == 0) {
        msgCtx->textDrawPos += (recomp_get_config_u32("text_speed") - 1);
        if (msgCtx->textDrawPos > msgCtx->decodedTextLen) {
            msgCtx->textDrawPos = msgCtx->decodedTextLen + 1;
        }
    }
}