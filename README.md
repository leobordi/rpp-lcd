### LED I2C DRIVER

Nel protocollo i2c si ha un bus, questo bus ha uno spazio di indirizzamento di 127 indirizzi, quindi si possono collegare 127 dispositivi diversi.
Una volta collegato il raspberry al bus i2c, per comunicare con il modulo i2c dell'lcd devo avere il suo indirizzo. guardando nella documentazione si capisce che è 0x27.
