#pragma once

class Configuration
{
	public:
		Configuration();
		Configuration(const Configuration& other);
		void setConfiguration(int* _config);
		void swapElements(int first, int second);
		int getElementAt(int _position) const;
		void randomize();
		int getBlankPosition();
		bool operator==(const Configuration& other) const;

	private:
		int iConfig[16];
};