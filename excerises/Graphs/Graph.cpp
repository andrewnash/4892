int main()
{
    std::ifstream       file("roadDistance.csv");

    CSVRow              row;
    while(file >> row)
    {
        std::cout << "4th Element(" << row[3] << ")\n";
    }
}