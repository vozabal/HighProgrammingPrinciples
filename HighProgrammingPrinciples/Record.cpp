class Record {

public:
		int id;
		double ist;
		double measuredat;

		Record();
		Record(int id, double ist, double measuredat) {
			this->id = id;
			this->ist = ist;
			this->measuredat = measuredat;
		}
};