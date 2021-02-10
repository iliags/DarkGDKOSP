#include "S3GE_Common.h"

//DGDK ID Management Initializers by Techlord
ResourceManager *dbMemblockResource = new ResourceManager(32);
ResourceManager *dbBitmapResource = new ResourceManager(32);
ResourceManager *dbImageResource =  new ResourceManager(4096);
ResourceManager *dbSpriteResource = new ResourceManager(4096);
ResourceManager *dbObjectResource = new ResourceManager(4096);
ResourceManager *dbMeshResource = new ResourceManager(64);
ResourceManager *dbSoundResource =  new ResourceManager(256);
ResourceManager *dbMusicResource =  new ResourceManager(64);
ResourceManager *dbCameraResource = new ResourceManager(4);
ResourceManager *dbLightResource =  new ResourceManager(8);
ResourceManager *FontResource =  new ResourceManager(20);
ResourceManager *S3GETextFontResource =  new ResourceManager(20);

string Output;