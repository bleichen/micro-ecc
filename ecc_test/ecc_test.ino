#include <j0g.h>
#include <js0n.h>

#include <lwm.h>

#include <bitlash.h>

#include <GS.h>

#include <SPI.h>
#include <Wire.h>
#include <Scout.h>
#include <Shell.h>


#include <ecc.h>

void setup() {
    Scout.setup();
    uint8_t l_private1[ECC_BYTES];
    uint8_t l_private2[ECC_BYTES];
    
    uint8_t l_public1[ECC_BYTES * 2];
    uint8_t l_public2[ECC_BYTES * 2];
    
    uint8_t l_secret1[ECC_BYTES];
    uint8_t l_secret2[ECC_BYTES];
    
    Serial.print("Testing ecc\n");
    
    unsigned long a = millis();
    ecc_make_key(l_public1, l_private1);
    unsigned long b = millis();
    
    Serial.print("Made key 1 in "); Serial.println(b-a);
    a = millis();
    ecc_make_key(l_public2, l_private2);
    b = millis();
    Serial.print("Made key 2 in "); Serial.println(b-a);

    a = millis();
    int r = ecdh_shared_secret(l_public2, l_private1, l_secret1);
    b = millis();
    Serial.print("Shared secret 1 in "); Serial.println(b-a);
    if(!r)
    {
        Serial.print("shared_secret() failed (1)\n");
        return;
    }

    a = millis();
    r = ecdh_shared_secret(l_public1, l_private2, l_secret2);
    b = millis();
    Serial.print("Shared secret 2 in "); Serial.println(b-a);
    if(!r)
    {
        Serial.print("shared_secret() failed (2)\n");
        return;
    }
    
    if(memcmp(l_secret1, l_secret2, sizeof(l_secret1)) != 0)
    {
        Serial.print("Shared secrets are not identical!\n");
        /*printf("Shared secret 1 = ");
        vli_print(l_secret1, ECC_BYTES);
        printf("\n");
        printf("Shared secret 2 = ");
        vli_print(l_secret2, ECC_BYTES);
        printf("\n");
        printf("Private key 1 = ");
        vli_print(l_private1, ECC_BYTES);
        printf("\n");
        printf("Private key 2 = ");
        vli_print(l_private2, ECC_BYTES);
        printf("\n");*/
    }
    else
    {
        Serial.print("Shared secrets are identical\n");
    }
}

void loop() {
  // put your main code here, to run repeatedly:

}
