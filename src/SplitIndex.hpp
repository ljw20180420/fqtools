#include <bits/stdc++.h>

class SplitIndex
{
private:
    std::string R1;
    std::string R2;
    std::string delimiter;

    void help(int argc, char **argv)
    {
        if (argc < 2 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help") || !strcmp(argv[1], "-help"))
        {
            std::cout << "fqtools split-index -R1 R1.fq -R2 R2.fq -delimiter \"str\"\n";
            std::cout << "    -delimiter: split R1 and R2 according to R1 index (address after delimiter)\n";
            exit(0);
        }
    }

    void parse(int argc, char **argv)
    {
        for (int i = 1; i < argc - 1; ++i)
        {
            if (!strcmp(argv[i], "-R1"))
                R1 = std::string(argv[i + 1]);
            if (!strcmp(argv[i], "-R2"))
                R2 = std::string(argv[i + 1]);
            if (!strcmp(argv[i], "-delimiter"))
                delimiter = std::string(argv[i + 1]);
        }
    }

    std::string suffix_addr(std::string &addr, std::string &delimiter)
    {
        int pos = addr.find_first_of(delimiter);
        return addr.substr(pos + delimiter.size());
    }

public:
    SplitIndex(int argc, char **argv)
    {
        help(argc, argv);
        parse(argc, argv);
    }

    void run()
    {
        std::map<std::string, std::pair<std::ofstream, std::ofstream>> fout_pairs;
        std::ifstream fin1(R1);
        std::ifstream fin2(R2);
        std::string addr1, addr2;
        getline(fin1, addr1);
        getline(fin2, addr2);
        while (fin1.good() && fin2.good())
        {
            std::string index1 = suffix_addr(addr1, delimiter);
            if (fout_pairs.try_emplace(
                              index1,
                              std::make_pair(
                                  std::ofstream(),
                                  std::ofstream()))
                    .second)
            {
                fout_pairs[index1].first.open(R1 + "." + std::to_string(fout_pairs.size()));
                fout_pairs[index1].second.open(R2 + "." + std::to_string(fout_pairs.size()));
            }

            for (int i = 0; i < 4; ++i)
            {
                fout_pairs[index1].first << addr1 << '\n';
                getline(fin1, addr1);
                fout_pairs[index1].second << addr2 << '\n';
                getline(fin2, addr2);
            }
        }
    }
};