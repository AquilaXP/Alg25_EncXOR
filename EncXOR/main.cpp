#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

void encrypt( std::istream& is, const std::vector<char>& key, std::ostream& os )
{
    char c = 0;
    size_t i = 0;
    while( is.get( c ) )
    {
        char r = key[i] ^ c;
        os.put( r );
        i += 1;
        if( i == key.size() )
            i = 0;
    }
}

int main( int ac, char* av[] )
{
    try
    {
        if( ac != 5 )
        {
            if( ( ac == 2 && av[1] == "-h" ) || ac == 1 )
            {
                std::cout << u8"XOR encription: -e|-d input_file key_file output_file\n";
                std::cout << u8"-e\tencrypt\n";
                std::cout << u8"-d\tdecrypt\n";
                return 0;
            }
            else
                throw std::runtime_error( "incorec input param: -e|-d input_file key_file output_file" );
        }

        std::string regime = av[1];
        fs::path input_file = av[2];
        fs::path key_file = av[3];
        fs::path output_file = av[4];

        std::ifstream ifs( input_file, std::ios::binary );
        if( !ifs.is_open() )
            throw std::runtime_error( "not open file: " + input_file.string() );

        std::ifstream ifsKey( key_file, std::ios::binary );
        if( !ifsKey.is_open() )
            throw std::runtime_error( "not open key: " + key_file.string() );

        std::vector< char > key( size_t( fs::file_size( key_file ) ) );
        if( !ifsKey.read( key.data(), key.size() ) )
            throw std::runtime_error( "fail read key" );

        std::ofstream ofs( output_file, std::ios::binary );
        if( !ofs.is_open() )
            throw std::runtime_error( "not open file: " + output_file.string() );

        if( regime == "-e" )
        {
            encrypt( ifs, key, ofs );
        }
        else if( regime == "-d" )
        {
            encrypt( ifs, key, ofs );
        }
        else
        {
            throw std::runtime_error( "incorect input console param" );
        }
    }
    catch( const std::exception& err )
    {
        std::cerr << err.what() << '\n';
        system( "pause" );
        return 1;
    }

    return 0;
}