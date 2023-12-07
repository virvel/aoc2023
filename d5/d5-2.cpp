#include "util.h"
using ulong = unsigned long long;

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

auto to_int_vec(std::vector<std::string> &v) {
    std::vector<ulong> d(v.size());
    auto stoi = [](auto &s) {return std::stoul(s);};
    std::transform(v.begin(), v.end(), d.begin(), stoi);
    return d;
}


struct map {
    
    struct tup {
        ulong dest;
        ulong src;
        ulong size;

        tup(ulong d, ulong s, ulong sz) {dest=d;src=s;size=sz;}
    };
   
    std::vector<tup> tups;

    const ulong operator()(ulong s) {
        for (auto &t:tups) { 
            if (s >= t.src and (s - t.src) < t.size) {
                s = t.dest - t.src + s; 
                return s;
            }
        }
        return s;
    }
    auto operator()(std::list<std::tuple<ulong, ulong>> ranges) {  
        std::list<std::tuple<ulong,ulong>> newranges {};

       /*print(ranges.size());
        for (auto&m:ranges)
            printf("[%llu, %llu] ", std::get<0>(m), std::get<1>(m));
        print("\n");
        */
        
        for (auto &r:ranges) {
            auto start = std::get<0>(r), end = std::get<1>(r);
                bool touched = false;
                for (auto& t: tups) { 
                    //printf("[%llu, %llu)\n", start, end);
                    //printf("\t[%llu, %llu) -> [%llu, %llu)\n", t.src, t.src+t.size, t.dest, t.dest+t.size);
                    if (start >= t.src && start < (t.src + t.size)) {
                        touched = true;
                        auto front = start - t.src + t.dest;
                        if (end < t.src + t.size) { 
                            auto back = end - t.src + t.dest;
                            newranges.push_back(std::make_pair( front, back ));
                        }
                        else {
                            newranges.push_back(std::make_pair(start + t.dest - t.src, t.dest + t.size-1));
                            if (t.src +t.size != end)
                                newranges.push_back(std::make_pair( t.src + t.size ,end ));
                            start = t.src + t.size;
                        }
                        break;
                    }
                    else if (end >= t.src && end < (t.src + t.size)) {
                        touched = true;
                        auto front = start;
                        auto back = t.src - 1;
                        if (front != back)
                            newranges.push_back(std::make_pair( front, back ));
                        newranges.push_back(std::make_pair(t.dest, end - t.src + t.dest));
                        end = t.src + t.size;
                        break;
                    }
                } 
                if (!touched) 
                    newranges.push_back(r);
                if (newranges.size() == 0)
                    newranges.push_back(r);
            }

        return newranges;
    }

};


int main(int argc, char *argv[]) {
    
    auto input = readfile(argv[1]);
        
    std::vector<ulong> seeds;

    auto tokens = split(input,"\n\n");
    auto seedss = split(split(tokens[0], ":")[1], " ");

    tokens.erase(tokens.begin());
    seeds = to_int_vec(seedss);
    std::vector<map> maps;

    for(unsigned t = 0; t < tokens.size(); ++t) {
        auto lines = split(tokens[t], "\n");
        
        map f;
        for (unsigned i = 1; i < lines.size(); ++i) {
            auto digits = split(lines[i], " ");
                auto d = to_int_vec(digits); 
                f.tups.push_back(map::tup(d[0], d[1], d[2]));
        }
        maps.push_back(f);
    }

    using tup = std::tuple<ulong, ulong>;
    using tupvec = std::vector<tup>;
    tupvec ranges;
    
    for (int i=0;i<seeds.size();i+=2) {
        ranges.push_back(std::make_pair(seeds[i], seeds[i+1]));
    }

    ulong res = std::numeric_limits<ulong>::max();

    std::list<std::tuple<ulong, ulong>> rngs;

    for (int i = 0; i < ranges.size(); ++i) {
        auto start = std::get<0>(ranges[i]);
        auto end = start+std::get<1>(ranges[i]);
        rngs.clear();
       
        auto seed_range = std::make_pair(start, end);
        rngs.push_back(seed_range);
        for (auto &f : maps) {
            rngs = f(rngs);
        }
        
        for (auto &r:rngs) {
            res = std::min(std::get<0>(r), res);
        }
         
    } 
    print(res);
}
