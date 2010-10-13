
#include "SHA3api_ref.h"
#include "fugue.h"

HashReturn
Init (hashState *state, int hashbitlen)
{
    if (Init_Fugue(state, hashbitlen)) return SUCCESS;
    return FAIL;
}

HashReturn
Update (hashState *state, const BitSequence *data, DataLength databitlen)
{
    if (!state || !state->Cfg)
        return FAIL;
    if (!databitlen)
        return SUCCESS;
    if (state->TotalBits&7)
        return FAIL;
    if (state->TotalBits&31)
    {
        int need = 32-(state->TotalBits&31);
        if (need>databitlen)
        {
            memcpy ((uint8*)state->Partial+((state->TotalBits&31)/8), data, (databitlen+7)/8);
            state->TotalBits += databitlen;
            return SUCCESS;
        }
        else
        {
            memcpy ((uint8*)state->Partial+((state->TotalBits&31)/8), data, need/8);
            Next_Fugue (state, state->Partial, 1);
            state->TotalBits += need;
            databitlen -= need;
            data += need/8;
        }
    }
    if (databitlen>31)
    {
        Next_Fugue (state, (uint32*)data, databitlen/32);
        state->TotalBits += (databitlen/32)*32;
        data += (databitlen/32)*4;
        databitlen &= 31;
    }
    if (databitlen)
    {
        memcpy ((uint8*)state->Partial, data, (databitlen+7)/8);
        state->TotalBits += databitlen;
    }
    return SUCCESS;
}

HashReturn
Final (hashState *state, BitSequence *hashval)
{
    if (!state || !state->Cfg)
        return FAIL;
    if (state->TotalBits&31)
    {
        int need = 32-(state->TotalBits&31);
        memset ((uint8*)state->Partial+(((state->TotalBits&31)+7)/8), 0, need/8);
        Next_Fugue (state, state->Partial, 1);
    }
    state->TotalBits = HO2BE_8 (state->TotalBits);
    Next_Fugue (state, (uint32*)&state->TotalBits, 2);
    Done_Fugue (state, (uint32*)hashval, NULL);
    return SUCCESS;
}

HashReturn
Hash (int hashbitlen, const BitSequence *data, DataLength databitlen, BitSequence *hashval)
{
    hashState HS;

    if (Init (&HS, hashbitlen) == SUCCESS)
        if (Update (&HS, data, databitlen) == SUCCESS)
            return Final (&HS, hashval);
    return FAIL;
}
