#include "LevelManager.h"

const unsigned short LEVEL[] = 
{16, 17, 71, 160, 264, 349, 451, 525, 629, 694, 764, 803, 899, 944, 1004, 1084, 1186, 54, 16, 8, 40960, 16400, 24608, 42048, 16464, 25696, 43136, 16528, 27808, 44224, 16592, 26848, 53, 1237, 2049, 2055, 2065, 2071, 2081, 2087, 2097, 2103, 2113, 2119, 2129, 2135, 2145, 2151, 2161, 2167, 2177, 2183, 2193, 2199, 2209, 2215, 2225, 2231, 2241, 2247, 2257, 2263, 2273, 2279, 2289, 2295, 3202, 3203, 3204, 3205, 3206, 89, 16, 16, 204, 40977, 16402, 24595, 1127, 42023, 16482, 25780, 43147, 16524, 27789, 2112, 2128, 2144, 2160, 2176, 2192, 2208, 2224, 2240, 2256, 2272, 2288, 2112, 2113, 2114, 2115, 2116, 2053, 2069, 2085, 2101, 2117, 2053, 2054, 2055, 2056, 2057, 2073, 2089, 2105, 2121, 2137, 2153, 2169, 2185, 2201, 2217, 2233, 2249, 2265, 2281, 2288, 2289, 2290, 2291, 2292, 2293, 2294, 2295, 2296, 2297, 2298, 2299, 2300, 2301, 2302, 2303, 2122, 2123, 2124, 2125, 2126, 2127, 2127, 2143, 2159, 2175, 2191, 2207, 2223, 2239, 2255, 2271, 2287, 2303, 104, 16, 16, 2054, 2055, 2056, 2057, 2058, 2059, 2060, 2061, 2062, 2063, 43027, 16404, 27669, 2070, 4124, 4125, 1054, 2079, 40995, 16420, 24613, 2086, 4140, 4141, 4142, 2095, 45107, 16436, 29749, 2102, 4156, 4157, 4158, 2111, 2112, 2113, 2114, 2115, 2116, 2117, 2118, 2127, 2128, 4182, 2143, 2144, 98, 3172, 4198, 2154, 2159, 2160, 4214, 2175, 2176, 2182, 2183, 2184, 2185, 2187, 2188, 2189, 2190, 2191, 2192, 3220, 2198, 2207, 2208, 2214, 44200, 42157, 2223, 2224, 2225, 2226, 2227, 2228, 2229, 2230, 16568, 16573, 2239, 2246, 26824, 25805, 2255, 2262, 2271, 2278, 2287, 2294, 2295, 2296, 2297, 2298, 2299, 2300, 2301, 2302, 2303, 85, 16, 16, 40960, 16385, 24578, 13321, 13322, 13323, 13324, 13325, 13326, 13327, 42000, 16401, 25618, 13336, 13337, 13338, 13343, 3112, 3113, 3114, 44, 13359, 44082, 13368, 13369, 13370, 13375, 16450, 13385, 13386, 13387, 13388, 13389, 13390, 13391, 26706, 13456, 13457, 13458, 13459, 13460, 13461, 13462, 13463, 13464, 13465, 13466, 13467, 13468, 13469, 13470, 13471, 13472, 13487, 13488, 54451, 16564, 31925, 13503, 13504, 13519, 13520, 1242, 13535, 13536, 13551, 13552, 13553, 13554, 13555, 13556, 13557, 13558, 13559, 13560, 13561, 13562, 13563, 13564, 13565, 13566, 13567, 102, 16, 15, 54272, 41985, 44034, 3075, 16400, 16401, 16402, 3091, 40988, 31776, 25633, 27682, 3107, 2085, 2086, 2087, 2088, 2089, 16428, 3120, 3121, 3122, 3123, 2101, 2105, 24636, 2117, 71, 2121, 2133, 2137, 2145, 2146, 2147, 2148, 2149, 2150, 2152, 2153, 2154, 2155, 2156, 2157, 2158, 2161, 2174, 13440, 13441, 13442, 13443, 13444, 13445, 13446, 13447, 13448, 13449, 13450, 43148, 2190, 2193, 2201, 13466, 16540, 2206, 2209, 2210, 2212, 2213, 2217, 13482, 27820, 2222, 2225, 2229, 2233, 13498, 2238, 2241, 1219, 2245, 2246, 2247, 2248, 2249, 13514, 2251, 2252, 2253, 2254, 2257, 2261, 13530, 2273, 2274, 2275, 2276, 2277, 13546, 13562, 74, 16, 16, 2048, 2049, 2050, 2051, 2052, 2053, 2054, 2055, 2056, 2057, 2058, 2059, 2060, 2061, 2062, 2063, 2064, 2079, 2080, 2095, 2096, 51, 41012, 16442, 2111, 2112, 16452, 2127, 2128, 24660, 2143, 2144, 2159, 2160, 8311, 2175, 2176, 49290, 2191, 2192, 2207, 2208, 2209, 2210, 2211, 2212, 2213, 2214, 2215, 2216, 2217, 2223, 2233, 2239, 2249, 2255, 25812, 2265, 2271, 2281, 43243, 16620, 27885, 2287, 2297, 2298, 2299, 2300, 2301, 2302, 2303, 104, 16, 16, 2054, 2055, 2056, 2057, 2058, 2059, 2060, 8209, 42003, 2070, 2076, 2077, 2078, 2079, 16419, 2086, 49193, 41004, 16429, 24622, 2095, 1073, 25651, 2102, 2108, 2109, 2110, 2111, 2112, 2113, 2114, 2115, 2116, 2117, 2118, 2119, 2120, 13385, 2122, 2123, 2124, 2125, 2126, 2127, 2128, 2136, 2138, 2143, 2144, 2152, 12393, 2154, 2159, 2160, 53363, 44149, 3196, 2175, 2176, 16515, 16517, 2191, 2192, 29843, 26773, 18588, 2207, 2208, 2223, 2224, 2239, 2240, 2241, 2242, 2243, 2244, 2245, 2246, 2247, 2248, 3273, 2250, 2251, 2252, 2253, 2254, 2255, 43220, 54486, 2264, 2266, 16612, 16614, 2280, 233, 2282, 27892, 31990, 2296, 2297, 2298, 65, 16, 16, 2049, 48144, 2065, 16416, 2081, 2091, 2092, 2093, 2094, 2095, 48176, 2097, 41019, 2108, 2113, 16459, 2124, 53325, 16462, 25679, 2129, 2138, 24667, 2140, 2145, 48228, 103, 2156, 12398, 2161, 16500, 2172, 2177, 27780, 53383, 2188, 2193, 2204, 2209, 2210, 2211, 7332, 2213, 2214, 2215, 2216, 2217, 2218, 2219, 2220, 2225, 43200, 2241, 2244, 48332, 16592, 2257, 16604, 27872, 2273, 27884, 2289, 70, 15, 9, 43015, 2056, 16407, 2072, 40994, 27687, 2088, 49, 16434, 2103, 2104, 24642, 2116, 2117, 14406, 2119, 2120, 2132, 14422, 2136, 2148, 1126, 2152, 2164, 2168, 2176, 3201, 2178, 2179, 2180, 2181, 2182, 2183, 2184, 2192, 2200, 2208, 44198, 2216, 2224, 55473, 2226, 2227, 2228, 16566, 2232, 2240, 42177, 16578, 31939, 2244, 26822, 2248, 2256, 16594, 25811, 2260, 2264, 2272, 2273, 2274, 2275, 2276, 2277, 2278, 2279, 2280, 39, 15, 9, 46080, 40968, 16400, 16408, 30752, 28712, 41026, 16451, 24644, 18501, 36934, 100, 5248, 5249, 5250, 5251, 5252, 5253, 5254, 5255, 5256, 54440, 13488, 13489, 13490, 16568, 42176, 13507, 31944, 16592, 1233, 13523, 18648, 25824, 13539, 37096, 96, 16, 16, 50176, 47105, 40962, 6148, 6149, 6150, 6151, 6152, 6153, 6154, 6155, 6156, 6157, 6158, 6159, 16400, 16401, 16402, 6164, 42008, 6175, 33824, 27681, 24610, 6180, 16424, 1068, 6191, 18480, 6194, 6195, 6196, 26680, 6207, 27712, 6210, 41027, 76, 6223, 6224, 6225, 6226, 16467, 6228, 6239, 6240, 14444, 6255, 6256, 16497, 16498, 6259, 6260, 41080, 16505, 32890, 6271, 6272, 25729, 31874, 6275, 6276, 6287, 6288, 6289, 6290, 6291, 6292, 6303, 6308, 6309, 6310, 6311, 6312, 6313, 9386, 6315, 6316, 6317, 6318, 6319, 6328, 6332, 6344, 55498, 6348, 6360, 6364, 6376, 6377, 6378, 6379, 6380, 45, 16, 16, 4096, 4112, 42011, 1053, 51259, 10301, 41027, 16452, 24645, 18502, 32839, 4180, 4181, 4182, 4183, 4196, 4197, 4199, 114, 4212, 25718, 4215, 4228, 4231, 4244, 4245, 4246, 4247, 4270, 4271, 4286, 45247, 4302, 16591, 4311, 4318, 27871, 4334, 18671, 4337, 4350, 34047, 60, 16, 16, 6144, 6148, 6149, 6162, 6167, 14372, 14373, 14388, 14389, 14404, 14405, 14406, 14407, 14408, 14409, 14410, 14411, 14412, 14413, 14414, 14415, 14420, 14421, 14422, 14423, 14424, 14425, 14426, 14427, 14428, 14429, 14430, 14431, 119, 41098, 16523, 24716, 49325, 6320, 6321, 16573, 47296, 6337, 36045, 16592, 6353, 27872, 6369, 6370, 6371, 6372, 6384, 55537, 16626, 31987, 6388, 8476, 80, 16, 16, 40960, 6145, 41986, 6147, 47108, 6149, 53254, 6151, 16400, 6161, 16402, 6163, 16404, 6165, 16406, 6167, 24608, 6177, 42018, 6179, 27684, 6181, 31782, 6183, 6192, 6193, 6194, 6195, 6196, 6197, 6198, 6199, 49236, 1110, 88, 56410, 16484, 16490, 27764, 8310, 15480, 26746, 35974, 18567, 18568, 12448, 12449, 12450, 12451, 12452, 12453, 12454, 12455, 12456, 12457, 12458, 12459, 12460, 12461, 12462, 12463, 6339, 6341, 6343, 6345, 42195, 50389, 55511, 25817, 6371, 6373, 6375, 6377, 6387, 6389, 6391, 6393, 102, 16, 13, 49152, 51201, 2050, 2057, 52234, 17419, 41996, 16400, 16401, 2066, 11284, 49174, 16407, 35864, 2073, 16410, 16412, 49184, 32801, 2082, 2089, 33834, 25644, 2096, 2097, 2098, 2099, 2100, 2104, 2105, 2112, 2121, 54346, 51276, 2128, 2137, 16474, 16476, 4192, 4193, 2153, 31850, 32876, 4208, 4209, 51320, 2169, 2176, 16520, 2185, 2186, 2187, 2188, 2192, 2193, 8340, 2198, 39064, 2202, 43168, 2209, 2216, 16560, 2225, 13490, 13491, 13492, 13493, 13494, 13495, 13496, 13497, 13498, 13500, 27840, 2241, 13506, 13507, 13508, 13509, 13510, 13511, 13512, 13513, 13514, 13516, 41168, 6353, 2265, 16608, 2273, 10468, 230, 24816, 2289, 2297, 2298, 2299, 2300, 120, 16, 16, 44033, 48133, 2055, 37896, 16393, 36874, 2059, 41996, 16397, 25614, 2063, 16401, 16405, 2071, 40984, 16409, 24602, 2075, 45084, 16413, 29726, 2079, 26657, 7203, 39973, 2087, 2088, 2089, 2090, 2091, 2092, 2093, 2094, 2095, 2103, 2111, 16451, 2119, 74, 2127, 2135, 2143, 2144, 2145, 2146, 2147, 2148, 2149, 2150, 2151, 10345, 3179, 2159, 55408, 55409, 2162, 2167, 2175, 17536, 16513, 2178, 14469, 2183, 2184, 2186, 2187, 2188, 2189, 2190, 2191, 42128, 33937, 2194, 2199, 2207, 18593, 2210, 2215, 2223, 26801, 2226, 2227, 2229, 2230, 2231, 7355, 2239, 2243, 4295, 2255, 2259, 2261, 2263, 2271, 2275, 2279, 2280, 2281, 2282, 2283, 2284, 2285, 2286, 2287, 2291, 2292, 2293, 2294, 2295, 43256, 16633, 27898, 2299, 51452, 16637, 33022, 2303}
;
const unsigned short *getLevel(int level) {
  return LEVEL + LEVEL[level];
}
