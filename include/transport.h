typedef struct transportInformation {
	int id, battery, autonomy;
	float price;
	char *type, *geocode;
	struct transportInformation* next;
} Transport;