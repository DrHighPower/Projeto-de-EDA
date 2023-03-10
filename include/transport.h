typedef struct transportInformation {
	int id, battery, autonomy;
	float price;
	char *type, *geocode;
	struct transportInformation* next;
} Transport;

int store_transports(Transport* transport, int bool);
int read_transports(Transport* transport, int bool);