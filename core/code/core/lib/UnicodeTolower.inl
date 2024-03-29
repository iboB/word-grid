// converted using table from: https://www.ibm.com/docs/en/i/7.2?topic=tables-unicode-lowercase-uppercase-conversion-mapping-table
// pasted into txt file and parsed with this ruby script:
// puts File.readlines('unicode-caps.txt').map { |line|
//  ar = line.strip.split("\t")
//  ar[3][' CAPITAL'] = ''
//  "{0x#{ar[1]}, 0x#{ar[0]}}, // #{ar[3]}\n"
// }.join

{0x0041, 0x0061}, // LATIN LETTER A
{0x0042, 0x0062}, // LATIN LETTER B
{0x0043, 0x0063}, // LATIN LETTER C
{0x0044, 0x0064}, // LATIN LETTER D
{0x0045, 0x0065}, // LATIN LETTER E
{0x0046, 0x0066}, // LATIN LETTER F
{0x0047, 0x0067}, // LATIN LETTER G
{0x0048, 0x0068}, // LATIN LETTER H
{0x0049, 0x0069}, // LATIN LETTER I
{0x004A, 0x006A}, // LATIN LETTER J
{0x004B, 0x006B}, // LATIN LETTER K
{0x004C, 0x006C}, // LATIN LETTER L
{0x004D, 0x006D}, // LATIN LETTER M
{0x004E, 0x006E}, // LATIN LETTER N
{0x004F, 0x006F}, // LATIN LETTER O
{0x0050, 0x0070}, // LATIN LETTER P
{0x0051, 0x0071}, // LATIN LETTER Q
{0x0052, 0x0072}, // LATIN LETTER R
{0x0053, 0x0073}, // LATIN LETTER S
{0x0054, 0x0074}, // LATIN LETTER T
{0x0055, 0x0075}, // LATIN LETTER U
{0x0056, 0x0076}, // LATIN LETTER V
{0x0057, 0x0077}, // LATIN LETTER W
{0x0058, 0x0078}, // LATIN LETTER X
{0x0059, 0x0079}, // LATIN LETTER Y
{0x005A, 0x007A}, // LATIN LETTER Z
{0x00C0, 0x00E0}, // LATIN LETTER A GRAVE
{0x00C1, 0x00E1}, // LATIN LETTER A ACUTE
{0x00C2, 0x00E2}, // LATIN LETTER A CIRCUMFLEX
{0x00C3, 0x00E3}, // LATIN LETTER A TILDE
{0x00C4, 0x00E4}, // LATIN LETTER A DIAERESIS
{0x00C5, 0x00E5}, // LATIN LETTER A RING
{0x00C6, 0x00E6}, // LATIN LETTER A E
{0x00C7, 0x00E7}, // LATIN LETTER C CEDILLA
{0x00C8, 0x00E8}, // LATIN LETTER E GRAVE
{0x00C9, 0x00E9}, // LATIN LETTER E ACUTE
{0x00CA, 0x00EA}, // LATIN LETTER E CIRCUMFLEX
{0x00CB, 0x00EB}, // LATIN LETTER E DIAERESIS
{0x00CC, 0x00EC}, // LATIN LETTER I GRAVE
{0x00CD, 0x00ED}, // LATIN LETTER I ACUTE
{0x00CE, 0x00EE}, // LATIN LETTER I CIRCUMFLEX
{0x00CF, 0x00EF}, // LATIN LETTER I DIAERESIS
{0x00D0, 0x00F0}, // LATIN LETTER ETH
{0x00D1, 0x00F1}, // LATIN LETTER N TILDE
{0x00D2, 0x00F2}, // LATIN LETTER O GRAVE
{0x00D3, 0x00F3}, // LATIN LETTER O ACUTE
{0x00D4, 0x00F4}, // LATIN LETTER O CIRCUMFLEX
{0x00D5, 0x00F5}, // LATIN LETTER O TILDE
{0x00D6, 0x00F6}, // LATIN LETTER O DIAERESIS
{0x00D8, 0x00F8}, // LATIN LETTER O SLASH
{0x00D9, 0x00F9}, // LATIN LETTER U GRAVE
{0x00DA, 0x00FA}, // LATIN LETTER U ACUTE
{0x00DB, 0x00FB}, // LATIN LETTER U CIRCUMFLEX
{0x00DC, 0x00FC}, // LATIN LETTER U DIAERESIS
{0x00DD, 0x00FD}, // LATIN LETTER Y ACUTE
{0x00DE, 0x00FE}, // LATIN LETTER THORN
{0x0178, 0x00FF}, // LATIN LETTER Y WITH DIAERESIS
{0x0100, 0x0101}, // LATIN LETTER A WITH MACRON
{0x0102, 0x0103}, // LATIN LETTER A WITH BREVE
{0x0104, 0x0105}, // LATIN LETTER A WITH OGONEK
{0x0106, 0x0107}, // LATIN LETTER C WITH ACUTE
{0x0108, 0x0109}, // LATIN LETTER C WITH CIRCUMFLEX
{0x010A, 0x010B}, // LATIN LETTER C WITH DOT ABOVE
{0x010C, 0x010D}, // LATIN LETTER C WITH CARON
{0x010E, 0x010F}, // LATIN LETTER D WITH CARON
{0x0110, 0x0111}, // LATIN LETTER D WITH STROKE
{0x0112, 0x0113}, // LATIN LETTER E WITH MACRON
{0x0114, 0x0115}, // LATIN LETTER E WITH BREVE
{0x0116, 0x0117}, // LATIN LETTER E WITH DOT ABOVE
{0x0118, 0x0119}, // LATIN LETTER E WITH OGONEK
{0x011A, 0x011B}, // LATIN LETTER E WITH CARON
{0x011C, 0x011D}, // LATIN LETTER G WITH CIRCUMFLEX
{0x011E, 0x011F}, // LATIN LETTER G WITH BREVE
{0x0120, 0x0121}, // LATIN LETTER G WITH DOT ABOVE
{0x0122, 0x0123}, // LATIN LETTER G WITH CEDILLA
{0x0124, 0x0125}, // LATIN LETTER H WITH CIRCUMFLEX
{0x0126, 0x0127}, // LATIN LETTER H WITH STROKE
{0x0128, 0x0129}, // LATIN LETTER I WITH TILDE
{0x012A, 0x012B}, // LATIN LETTER I WITH MACRON
{0x012C, 0x012D}, // LATIN LETTER I WITH BREVE
{0x012E, 0x012F}, // LATIN LETTER I WITH OGONEK
{0x0049, 0x0131}, // LATIN LETTER I
{0x0132, 0x0133}, // LATIN LIGATURE IJ
{0x0134, 0x0135}, // LATIN LETTER J WITH CIRCUMFLEX
{0x0136, 0x0137}, // LATIN LETTER K WITH CEDILLA
{0x0139, 0x013A}, // LATIN LETTER L WITH ACUTE
{0x013B, 0x013C}, // LATIN LETTER L WITH CEDILLA
{0x013D, 0x013E}, // LATIN LETTER L WITH CARON
{0x013F, 0x0140}, // LATIN LETTER L WITH MIDDLE DOT
{0x0141, 0x0142}, // LATIN LETTER L WITH STROKE
{0x0143, 0x0144}, // LATIN LETTER N WITH ACUTE
{0x0145, 0x0146}, // LATIN LETTER N WITH CEDILLA
{0x0147, 0x0148}, // LATIN LETTER N WITH CARON
{0x014A, 0x014B}, // LATIN LETTER ENG (SAMI)
{0x014C, 0x014D}, // LATIN LETTER O WITH MACRON
{0x014E, 0x014F}, // LATIN LETTER O WITH BREVE
{0x0150, 0x0151}, // LATIN LETTER O WITH DOUBLE ACUTE
{0x0152, 0x0153}, // LATIN LIGATURE OE
{0x0154, 0x0155}, // LATIN LETTER R WITH ACUTE
{0x0156, 0x0157}, // LATIN LETTER R WITH CEDILLA
{0x0158, 0x0159}, // LATIN LETTER R WITH CARON
{0x015A, 0x015B}, // LATIN LETTER S WITH ACUTE
{0x015C, 0x015D}, // LATIN LETTER S WITH CIRCUMFLEX
{0x015E, 0x015F}, // LATIN LETTER S WITH CEDILLA
{0x0160, 0x0161}, // LATIN LETTER S WITH CARON
{0x0162, 0x0163}, // LATIN LETTER T WITH CEDILLA
{0x0164, 0x0165}, // LATIN LETTER T WITH CARON
{0x0166, 0x0167}, // LATIN LETTER T WITH STROKE
{0x0168, 0x0169}, // LATIN LETTER U WITH TILDE
{0x016A, 0x016B}, // LATIN LETTER U WITH MACRON
{0x016C, 0x016D}, // LATIN LETTER U WITH BREVE
{0x016E, 0x016F}, // LATIN LETTER U WITH RING ABOVE
{0x0170, 0x0171}, // LATIN LETTER U WITH DOUBLE ACUTE
{0x0172, 0x0173}, // LATIN LETTER U WITH OGONEK
{0x0174, 0x0175}, // LATIN LETTER W WITH CIRCUMFLEX
{0x0176, 0x0177}, // LATIN LETTER Y WITH CIRCUMFLEX
{0x0179, 0x017A}, // LATIN LETTER Z WITH ACUTE
{0x017B, 0x017C}, // LATIN LETTER Z WITH DOT ABOVE
{0x017D, 0x017E}, // LATIN LETTER Z WITH CARON
{0x0182, 0x0183}, // LATIN LETTER B WITH TOPBAR
{0x0184, 0x0185}, // LATIN LETTER TONE SIX
{0x0187, 0x0188}, // LATIN LETTER C WITH HOOK
{0x018B, 0x018C}, // LATIN LETTER D WITH TOPBAR
{0x0191, 0x0192}, // LATIN LETTER F WITH HOOK
{0x0198, 0x0199}, // LATIN LETTER K WITH HOOK
{0x01A0, 0x01A1}, // LATIN LETTER O WITH HORN
{0x01A2, 0x01A3}, // LATIN LETTER OI
{0x01A4, 0x01A5}, // LATIN LETTER P WITH HOOK
{0x01A7, 0x01A8}, // LATIN LETTER TONE TWO
{0x01AC, 0x01AD}, // LATIN LETTER T WITH HOOK
{0x01AF, 0x01B0}, // LATIN LETTER U WITH HORN
{0x01B3, 0x01B4}, // LATIN LETTER Y WITH HOOK
{0x01B5, 0x01B6}, // LATIN LETTER Z WITH STROKE
{0x01B8, 0x01B9}, // LATIN LETTER EZH REVERSED
{0x01BC, 0x01BD}, // LATIN LETTER TONE FIVE
{0x01C4, 0x01C6}, // LATIN LETTER DZ WITH CARON
{0x01C7, 0x01C9}, // LATIN LETTER LJ
{0x01CA, 0x01CC}, // LATIN LETTER NJ
{0x01CD, 0x01CE}, // LATIN LETTER A WITH CARON
{0x01CF, 0x01D0}, // LATIN LETTER I WITH CARON
{0x01D1, 0x01D2}, // LATIN LETTER O WITH CARON
{0x01D3, 0x01D4}, // LATIN LETTER U WITH CARON
{0x01D5, 0x01D6}, // LATIN LETTER U WITH DIAERESIS AND MACRON
{0x01D7, 0x01D8}, // LATIN LETTER U WITH DIAERESIS AND ACUTE
{0x01D9, 0x01DA}, // LATIN LETTER U WITH DIAERESIS AND CARON
{0x01DB, 0x01DC}, // LATIN LETTER U WITH DIAERESIS AND GRAVE
{0x01DE, 0x01DF}, // LATIN LETTER A WITH DIAERESIS AND MACRON
{0x01E0, 0x01E1}, // LATIN LETTER A WITH DOT ABOVE AND MACRON
{0x01E2, 0x01E3}, // LATIN LIGATURE AE MTH MACRON
{0x01E4, 0x01E5}, // LATIN LETTER G WITH STROKE
{0x01E6, 0x01E7}, // LATIN LETTER G WITH CARON
{0x01E8, 0x01E9}, // LATIN LETTER K WITH CARON
{0x01EA, 0x01EB}, // LATIN LETTER O WITH OGONEK
{0x01EC, 0x01ED}, // LATIN LETTER O WITH OGONEK AND MACRON
{0x01EE, 0x01EF}, // LATIN LETTER EZH WITH CARON
{0x01F1, 0x01F3}, // LATIN LETTER DZ
{0x01F4, 0x01F5}, // LATIN LETTER G WITH ACUTE
{0x01FA, 0x01FB}, // LATIN LETTER A WITH RING ABOVE AND ACUTE
{0x01FC, 0x01FD}, // LATIN LIGATURE AE WITH ACUTE
{0x01FE, 0x01FF}, // LATIN LETTER O WITH STROKE AND ACUTE
{0x0200, 0x0201}, // LATIN LETTER A WITH DOUBLE GRAVE
{0x0202, 0x0203}, // LATIN LETTER A WITH INVERTED BREVE
{0x0204, 0x0205}, // LATIN LETTER E WITH DOUBLE GRAVE
{0x0206, 0x0207}, // LATIN LETTER E WITH INVERTED BREVE
{0x0208, 0x0209}, // LATIN LETTER I WITH DOUBLE GRAVE
{0x020A, 0x020B}, // LATIN LETTER I WITH INVERTED BREVE
{0x020C, 0x020D}, // LATIN LETTER O WITH DOUBLE GRAVE
{0x020E, 0x020F}, // LATIN LETTER O WITH INVERTED BREVE
{0x0210, 0x0211}, // LATIN LETTER R WITH DOUBLE GRAVE
{0x0212, 0x0213}, // LATIN LETTER R WITH INVERTED BREVE
{0x0214, 0x0215}, // LATIN LETTER U WITH DOUBLE GRAVE
{0x0216, 0x0217}, // LATIN LETTER U WITH INVERTED BREVE
{0x0181, 0x0253}, // LATIN LETTER B WITH HOOK
{0x0186, 0x0254}, // LATIN LETTER OPEN O
{0x018A, 0x0257}, // LATIN LETTER D WITH HOOK
{0x018E, 0x0258}, // LATIN LETTER REVERSED E
{0x018F, 0x0259}, // LATIN LETTER SCHWA
{0x0190, 0x025B}, // LATIN LETTER OPEN E
{0x0193, 0x0260}, // LATIN LETTER G WITH HOOK
{0x0194, 0x0263}, // LATIN LETTER GAMMA
{0x0197, 0x0268}, // LATIN LETTER I WITH STROKE
{0x0196, 0x0269}, // LATIN LETTER IOTA
{0x019C, 0x026F}, // LATIN LETTER TURNED M
{0x019D, 0x0272}, // LATIN LETTER N WITH LEFT HOOK
{0x019F, 0x0275}, // LATIN LETTER O WITH MIDDLE TILDE
{0x01A9, 0x0283}, // LATIN LETTER ESH
{0x01AE, 0x0288}, // LATIN LETTER T WITH RETROFLEX HOOK
{0x01B1, 0x028A}, // LATIN LETTER UPSILON
{0x01B2, 0x028B}, // LATIN LETTER V WITH HOOK
{0x01B7, 0x0292}, // LATIN LETTER EZH
{0x0386, 0x03AC}, // GREEK LETTER ALPHA WITH TONOS
{0x0388, 0x03AD}, // GREEK LETTER EPSILON WITH TONOS
{0x0389, 0x03AE}, // GREEK LETTER ETA WITH TONOS
{0x038A, 0x03AF}, // GREEK LETTER IOTA WITH TONOS
{0x0391, 0x03B1}, // GREEK LETTER ALPHA
{0x0392, 0x03B2}, // GREEK LETTER BETA
{0x0393, 0x03B3}, // GREEK LETTER GAMMA
{0x0394, 0x03B4}, // GREEK LETTER DELTA
{0x0395, 0x03B5}, // GREEK LETTER EPSILON
{0x0396, 0x03B6}, // GREEK LETTER ZETA
{0x0397, 0x03B7}, // GREEK LETTER ETA
{0x0398, 0x03B8}, // GREEK LETTER THETA
{0x0399, 0x03B9}, // GREEK LETTER IOTA
{0x039A, 0x03BA}, // GREEK LETTER KAPPA
{0x039B, 0x03BB}, // GREEK LETTER LAMDA
{0x039C, 0x03BC}, // GREEK LETTER MU
{0x039D, 0x03BD}, // GREEK LETTER NU
{0x039E, 0x03BE}, // GREEK LETTER XI
{0x039F, 0x03BF}, // GREEK LETTER OMICRON
{0x03A0, 0x03C0}, // GREEK LETTER PI
{0x03A1, 0x03C1}, // GREEK LETTER RHO
{0x03A3, 0x03C3}, // GREEK LETTER SIGMA
{0x03A4, 0x03C4}, // GREEK LETTER TAU
{0x03A5, 0x03C5}, // GREEK LETTER UPSILON
{0x03A6, 0x03C6}, // GREEK LETTER PHI
{0x03A7, 0x03C7}, // GREEK LETTER CHI
{0x03A8, 0x03C8}, // GREEK LETTER PSI
{0x03A9, 0x03C9}, // GREEK LETTER OMEGA
{0x03AA, 0x03CA}, // GREEK LETTER IOTA WITH DIALYTIKA
{0x03AB, 0x03CB}, // GREEK LETTER UPSILON WITH DIALYTIKA
{0x038C, 0x03CC}, // GREEK LETTER OMICRON WITH TONOS
{0x038E, 0x03CD}, // GREEK LETTER UPSILON WITH TONOS
{0x038F, 0x03CE}, // GREEK LETTER OMEGA WITH TONOS
{0x03E2, 0x03E3}, // COPTIC LETTER SHEI
{0x03E4, 0x03E5}, // COPTIC LETTER FEI
{0x03E6, 0x03E7}, // COPTIC LETTER KHEI
{0x03E8, 0x03E9}, // COPTIC LETTER HORI
{0x03EA, 0x03EB}, // COPTIC LETTER GANGIA
{0x03EC, 0x03ED}, // COPTIC LETTER SHIMA
{0x03EE, 0x03EF}, // COPTIC LETTER DEI
{0x0410, 0x0430}, // CYRILLIC LETTER A
{0x0411, 0x0431}, // CYRILLIC LETTER BE
{0x0412, 0x0432}, // CYRILLIC LETTER VE
{0x0413, 0x0433}, // CYRILLIC LETTER GHE
{0x0414, 0x0434}, // CYRILLIC LETTER DE
{0x0415, 0x0435}, // CYRILLIC LETTER IE
{0x0416, 0x0436}, // CYRILLIC LETTER ZHE
{0x0417, 0x0437}, // CYRILLIC LETTER ZE
{0x0418, 0x0438}, // CYRILLIC LETTER I
{0x0419, 0x0439}, // CYRILLIC LETTER SHORT I
{0x041A, 0x043A}, // CYRILLIC LETTER KA
{0x041B, 0x043B}, // CYRILLIC LETTER EL
{0x041C, 0x043C}, // CYRILLIC LETTER EM
{0x041D, 0x043D}, // CYRILLIC LETTER EN
{0x041E, 0x043E}, // CYRILLIC LETTER O
{0x041F, 0x043F}, // CYRILLIC LETTER PE
{0x0420, 0x0440}, // CYRILLIC LETTER ER
{0x0421, 0x0441}, // CYRILLIC LETTER ES
{0x0422, 0x0442}, // CYRILLIC LETTER TE
{0x0423, 0x0443}, // CYRILLIC LETTER U
{0x0424, 0x0444}, // CYRILLIC LETTER EF
{0x0425, 0x0445}, // CYRILLIC LETTER HA
{0x0426, 0x0446}, // CYRILLIC LETTER TSE
{0x0427, 0x0447}, // CYRILLIC LETTER CHE
{0x0428, 0x0448}, // CYRILLIC LETTER SHA
{0x0429, 0x0449}, // CYRILLIC LETTER SHCHA
{0x042A, 0x044A}, // CYRILLIC LETTER HARD SIGN
{0x042B, 0x044B}, // CYRILLIC LETTER YERU
{0x042C, 0x044C}, // CYRILLIC LETTER SOFT SIGN
{0x042D, 0x044D}, // CYRILLIC LETTER E
{0x042E, 0x044E}, // CYRILLIC LETTER YU
{0x042F, 0x044F}, // CYRILLIC LETTER YA
{0x0401, 0x0451}, // CYRILLIC LETTER IO
{0x0402, 0x0452}, // CYRILLIC LETTER DJE (SERBOCROATIAN)
{0x0403, 0x0453}, // CYRILLIC LETTER GJE
{0x0404, 0x0454}, // CYRILLIC LETTER UKRAINIAN IE
{0x0405, 0x0455}, // CYRILLIC LETTER DZE
{0x0406, 0x0456}, // CYRILLIC LETTER BYELORUSSIAN_UKRAINIAN I
{0x0407, 0x0457}, // CYRILLIC LETTER YI (UKRAINIAN)
{0x0408, 0x0458}, // CYRILLIC LETTER JE
{0x0409, 0x0459}, // CYRILLIC LETTER LJE
{0x040A, 0x045A}, // CYRILLIC LETTER NJE
{0x040B, 0x045B}, // CYRILLIC LETTER TSHE (SERBOCROATIAN)
{0x040C, 0x045C}, // CYRILLIC LETTER KJE
{0x040E, 0x045E}, // CYRILLIC LETTER SHORT U (BYELORUSSIAN)
{0x040F, 0x045F}, // CYRILLIC LETTER DZHE
{0x0460, 0x0461}, // CYRILLIC LETTER OMEGA
{0x0462, 0x0463}, // CYRILLIC LETTER YAT
{0x0464, 0x0465}, // CYRILLIC LETTER IOTIFIED E
{0x0466, 0x0467}, // CYRILLIC LETTER LITTLE YUS
{0x0468, 0x0469}, // CYRILLIC LETTER IOTIFIED LITTLE YUS
{0x046A, 0x046B}, // CYRILLIC LETTER BIG YUS
{0x046C, 0x046D}, // CYRILLIC LETTER IOTIFIED BIG YUS
{0x046E, 0x046F}, // CYRILLIC LETTER KSI
{0x0470, 0x0471}, // CYRILLIC LETTER PSI
{0x0472, 0x0473}, // CYRILLIC LETTER FITA
{0x0474, 0x0475}, // CYRILLIC LETTER IZHITSA
{0x0476, 0x0477}, // CYRILLIC LETTER IZHITSA WITH DOUBLE GRAVE ACCENT
{0x0478, 0x0479}, // CYRILLIC LETTER UK
{0x047A, 0x047B}, // CYRILLIC LETTER ROUND OMEGA
{0x047C, 0x047D}, // CYRILLIC LETTER OMEGA WITH TITLO
{0x047E, 0x047F}, // CYRILLIC LETTER OT
{0x0480, 0x0481}, // CYRILLIC LETTER KOPPA
{0x0490, 0x0491}, // CYRILLIC LETTER GHE WITH UPTURN
{0x0492, 0x0493}, // CYRILLIC LETTER GHE WITH STROKE
{0x0494, 0x0495}, // CYRILLIC LETTER GHE WITH MIDDLE HOOK
{0x0496, 0x0497}, // CYRILLIC LETTER ZHE WITH DESCENDER
{0x0498, 0x0499}, // CYRILLIC LETTER ZE WITH DESCENDER
{0x049A, 0x049B}, // CYRILLIC LETTER KA WITH DESCENDER
{0x049C, 0x049D}, // CYRILLIC LETTER KA WITH VERTICAL STROKE
{0x049E, 0x049F}, // CYRILLIC LETTER KA WITH STROKE
{0x04A0, 0x04A1}, // CYRILLIC LETTER BASHKIR KA
{0x04A2, 0x04A3}, // CYRILLIC LETTER EN WITH DESCENDER
{0x04A4, 0x04A5}, // CYRILLIC LIGATURE EN GHF
{0x04A6, 0x04A7}, // CYRILLIC LETTER PE WITH MIDDLE HOOK (ABKHASIAN)
{0x04A8, 0x04A9}, // CYRILLIC LETTER ABKHASIAN HA
{0x04AA, 0x04AB}, // CYRILLIC LETTER ES WITH DESCENDER
{0x04AC, 0x04AD}, // CYRILLIC LETTER TE WITH DESCENDER
{0x04AE, 0x04AF}, // CYRILLIC LETTER STRAIGHT U
{0x04B0, 0x04B1}, // CYRILLIC LETTER STRAIGHT U WITH STROKE
{0x04B2, 0x04B3}, // CYRILLIC LETTER HA WITH DESCENDER
{0x04B4, 0x04B5}, // CYRILLIC LIGATURE TE TSE (ABKHASIAN)
{0x04B6, 0x04B7}, // CYRILLIC LETTER CHE WITH DESCENDER
{0x04B8, 0x04B9}, // CYRILLIC LETTER CHE WITH VERTICAL STROKE
{0x04BA, 0x04BB}, // CYRILLIC LETTER SHHA
{0x04BC, 0x04BD}, // CYRILLIC LETTER ABKHASIAN CHE
{0x04BE, 0x04BF}, // CYRILLIC LETTER ABKHASIAN CHE WITH DESCENDER
{0x04C1, 0x04C2}, // CYRILLIC LETTER ZHE WITH BREVE
{0x04C3, 0x04C4}, // CYRILLIC LETTER KA WITH HOOK
{0x04C7, 0x04C8}, // CYRILLIC LETTER EN WITH HOOK
{0x04CB, 0x04CC}, // CYRILLIC LETTER KHAKASSIAN CHE
{0x04D0, 0x04D1}, // CYRILLIC LETTER A WITH BREVE
{0x04D2, 0x04D3}, // CYRILLIC LETTER A WITH DIAERESIS
{0x04D4, 0x04D5}, // CYRILLIC LIGATURE A IE
{0x04D6, 0x04D7}, // CYRILLIC LETTER IE WITH BREVE
{0x04D8, 0x04D9}, // CYRILLIC LETTER SCHWA
{0x04DA, 0x04DB}, // CYRILLIC LETTER SCHWA WITH DIAERESIS
{0x04DC, 0x04DD}, // CYRILLIC LETTER ZHE WITH DIAERESIS
{0x04DE, 0x04DF}, // CYRILLIC LETTER ZE WITH DIAERESIS
{0x04E0, 0x04E1}, // CYRILLIC LETTER ABKHASIAN DZE
{0x04E2, 0x04E3}, // CYRILLIC LETTER I WITH MACRON
{0x04E4, 0x04E5}, // CYRILLIC LETTER I WITH DIAERESIS
{0x04E6, 0x04E7}, // CYRILLIC LETTER O WITH DIAERESIS
{0x04E8, 0x04E9}, // CYRILLIC LETTER BARRED O
{0x04EA, 0x04EB}, // CYRILLIC LETTER BARRED O WITH DIAERESIS
{0x04EE, 0x04EF}, // CYRILLIC LETTER U WITH MACRON
{0x04F0, 0x04F1}, // CYRILLIC LETTER U WITH DIAERESIS
{0x04F2, 0x04F3}, // CYRILLIC LETTER U WITH DOUBLE ACUTE
{0x04F4, 0x04F5}, // CYRILLIC LETTER CHE WITH DIAERESIS
{0x04F8, 0x04F9}, // CYRILLIC LETTER YERU WITH DIAERESIS
{0x0531, 0x0561}, // ARMENIAN LETTER AYB
{0x0532, 0x0562}, // ARMENIAN LETTER BEN
{0x0533, 0x0563}, // ARMENIAN LETTER GIM
{0x0534, 0x0564}, // ARMENIAN LETTER DA
{0x0535, 0x0565}, // ARMENIAN LETTER ECH
{0x0536, 0x0566}, // ARMENIAN LETTER ZA
{0x0537, 0x0567}, // ARMENIAN LETTER EH
{0x0538, 0x0568}, // ARMENIAN LETTER ET
{0x0539, 0x0569}, // ARMENIAN LETTER TO
{0x053A, 0x056A}, // ARMENIAN LETTER ZHE
{0x053B, 0x056B}, // ARMENIAN LETTER INI
{0x053C, 0x056C}, // ARMENIAN LETTER LIWN
{0x053D, 0x056D}, // ARMENIAN LETTER XEH
{0x053E, 0x056E}, // ARMENIAN LETTER CA
{0x053F, 0x056F}, // ARMENIAN LETTER KEN
{0x0540, 0x0570}, // ARMENIAN LETTER HO
{0x0541, 0x0571}, // ARMENIAN LETTER JA
{0x0542, 0x0572}, // ARMENIAN LETTER GHAD
{0x0543, 0x0573}, // ARMENIAN LETTER CHEH
{0x0544, 0x0574}, // ARMENIAN LETTER MEN
{0x0545, 0x0575}, // ARMENIAN LETTER YI
{0x0546, 0x0576}, // ARMENIAN LETTER NOW
{0x0547, 0x0577}, // ARMENIAN LETTER SHA
{0x0548, 0x0578}, // ARMENIAN LETTER VO
{0x0549, 0x0579}, // ARMENIAN LETTER CHA
{0x054A, 0x057A}, // ARMENIAN LETTER PEH
{0x054B, 0x057B}, // ARMENIAN LETTER JHEH
{0x054C, 0x057C}, // ARMENIAN LETTER RA
{0x054D, 0x057D}, // ARMENIAN LETTER SEH
{0x054E, 0x057E}, // ARMENIAN LETTER VEW
{0x054F, 0x057F}, // ARMENIAN LETTER TIWN
{0x0550, 0x0580}, // ARMENIAN LETTER REH
{0x0551, 0x0581}, // ARMENIAN LETTER CO
{0x0552, 0x0582}, // ARMENIAN LETTER YIWN
{0x0553, 0x0583}, // ARMENIAN LETTER PIWR
{0x0554, 0x0584}, // ARMENIAN LETTER KEH
{0x0555, 0x0585}, // ARMENIAN LETTER OH
{0x0556, 0x0586}, // ARMENIAN LETTER FEH
{0x10A0, 0x10D0}, // GEORGIAN LETTER AN (KHUTSURI)
{0x10A1, 0x10D1}, // GEORGIAN LETTER BAN (KHUTSURI)
{0x10A2, 0x10D2}, // GEORGIAN LETTER GAN (KHUTSURI)
{0x10A3, 0x10D3}, // GEORGIAN LETTER DON (KHUTSURI)
{0x10A4, 0x10D4}, // GEORGIAN LETTER EN (KHUTSURI)
{0x10A5, 0x10D5}, // GEORGIAN LETTER VIN (KHUTSURI)
{0x10A6, 0x10D6}, // GEORGIAN LETTER ZEN (KHUTSURI)
{0x10A7, 0x10D7}, // GEORGIAN LETTER TAN (KHUTSURI)
{0x10A8, 0x10D8}, // GEORGIAN LETTER IN (KHUTSURI)
{0x10A9, 0x10D9}, // GEORGIAN LETTER KAN (KHUTSURI)
{0x10AA, 0x10DA}, // GEORGIAN LETTER LAS (KHUTSURI)
{0x10AB, 0x10DB}, // GEORGIAN LETTER MAN (KHUTSURI)
{0x10AC, 0x10DC}, // GEORGIAN LETTER NAR (KHUTSURI)
{0x10AD, 0x10DD}, // GEORGIAN LETTER ON (KHUTSURI)
{0x10AE, 0x10DE}, // GEORGIAN LETTER PAR (KHUTSURI)
{0x10AF, 0x10DF}, // GEORGIAN LETTER ZHAR (KHUTSURI)
{0x10B0, 0x10E0}, // GEORGIAN LETTER RAE (KHUTSURI)
{0x10B1, 0x10E1}, // GEORGIAN LETTER SAN (KHUTSURI)
{0x10B2, 0x10E2}, // GEORGIAN LETTER TAR (KHUTSURI)
{0x10B3, 0x10E3}, // GEORGIAN LETTER UN (KHUTSURI)
{0x10B4, 0x10E4}, // GEORGIAN LETTER PHAR (KHUTSURI)
{0x10B5, 0x10E5}, // GEORGIAN LETTER KHAR (KHUTSURI)
{0x10B6, 0x10E6}, // GEORGIAN LETTER GHAN (KHUTSURI)
{0x10B7, 0x10E7}, // GEORGIAN LETTER QAR (KHUTSURI)
{0x10B8, 0x10E8}, // GEORGIAN LETTER SHIN (KHUTSURI)
{0x10B9, 0x10E9}, // GEORGIAN LETTER CHIN (KHUTSURI)
{0x10BA, 0x10EA}, // GEORGIAN LETTER CAN (KHUTSURI)
{0x10BB, 0x10EB}, // GEORGIAN LETTER JIL (KHUTSURI)
{0x10BC, 0x10EC}, // GEORGIAN LETTER CIL (KHUTSURI)
{0x10BD, 0x10ED}, // GEORGIAN LETTER CHAR (KHUTSURI)
{0x10BE, 0x10EE}, // GEORGIAN LETTER XAN (KHUTSURI)
{0x10BF, 0x10EF}, // GEORGIAN LETTER JHAN (KHUTSURI)
{0x10C0, 0x10F0}, // GEORGIAN LETTER HAE (KHUTSURI)
{0x10C1, 0x10F1}, // GEORGIAN LETTER HE (KHUTSURI)
{0x10C2, 0x10F2}, // GEORGIAN LETTER HIE (KHUTSURI)
{0x10C3, 0x10F3}, // GEORGIAN LETTER WE (KHUTSURI)
{0x10C4, 0x10F4}, // GEORGIAN LETTER HAR (KHUTSURI)
{0x10C5, 0x10F5}, // GEORGIAN LETTER HOE (KHUTSURI)
{0x1E00, 0x1E01}, // LATIN LETTER A WITH RING BELOW
{0x1E02, 0x1E03}, // LATIN LETTER B WITH DOT ABOVE
{0x1E04, 0x1E05}, // LATIN LETTER B WITH DOT BELOW
{0x1E06, 0x1E07}, // LATIN LETTER B WITH LINE BELOW
{0x1E08, 0x1E09}, // LATIN LETTER C WITH CEDILLA AND ACUTE
{0x1E0A, 0x1E0B}, // LATIN LETTER D WITH DOT ABOVE
{0x1E0C, 0x1E0D}, // LATIN LETTER D WITH DOT BELOW
{0x1E0E, 0x1E0F}, // LATIN LETTER D WITH LINE BELOW
{0x1E10, 0x1E11}, // LATIN LETTER D WITH CEDILLA
{0x1E12, 0x1E13}, // LATIN LETTER D WITH CIRCUMFLEX BELOW
{0x1E14, 0x1E15}, // LATIN LETTER E WITH MACRON AND GRAVE
{0x1E16, 0x1E17}, // LATIN LETTER E WITH MACRON AND ACUTE
{0x1E18, 0x1E19}, // LATIN LETTER E WITH CIRCUMFLEX BELOW
{0x1E1A, 0x1E1B}, // LATIN LETTER E WITH TILDE BELOW
{0x1E1C, 0x1E1D}, // LATIN LETTER E WITH CEDILLA AND BREVE
{0x1E1E, 0x1E1F}, // LATIN LETTER F WITH DOT ABOVE
{0x1E20, 0x1E21}, // LATIN LETTER G WITH MACRON
{0x1E22, 0x1E23}, // LATIN LETTER H WITH DOT ABOVE
{0x1E24, 0x1E25}, // LATIN LETTER H WITH DOT BELOW
{0x1E26, 0x1E27}, // LATIN LETTER H WITH DIAERESIS
{0x1E28, 0x1E29}, // LATIN LETTER H WITH CEDILLA
{0x1E2A, 0x1E2B}, // LATIN LETTER H WITH BREVE BELOW
{0x1E2C, 0x1E2D}, // LATIN LETTER I WITH TILDE BELOW
{0x1E2E, 0x1E2F}, // LATIN LETTER I WITH DIAERESIS AND ACUTE
{0x1E30, 0x1E31}, // LATIN LETTER K WITH ACUTE
{0x1E32, 0x1E33}, // LATIN LETTER K WITH DOT BELOW
{0x1E34, 0x1E35}, // LATIN LETTER K WITH LINE BELOW
{0x1E36, 0x1E37}, // LATIN LETTER L WITH DOT BELOW
{0x1E38, 0x1E39}, // LATIN LETTER L WITH DOT BELOW AND MACRON
{0x1E3A, 0x1E3B}, // LATIN LETTER L WITH LINE BELOW
{0x1E3C, 0x1E3D}, // LATIN LETTER L WITH CIRCUMFLEX BELOW
{0x1E3E, 0x1E3F}, // LATIN LETTER M WITH ACUTE
{0x1E40, 0x1E41}, // LATIN LETTER M WITH DOT ABOVE
{0x1E42, 0x1E43}, // LATIN LETTER M WITH DOT BELOW
{0x1E44, 0x1E45}, // LATIN LETTER N WITH DOT ABOVE
{0x1E46, 0x1E47}, // LATIN LETTER N WITH DOT BELOW
{0x1E48, 0x1E49}, // LATIN LETTER N WITH LINE BELOW
{0x1E4A, 0x1E4B}, // LATIN LETTER N WITH CIRCUMFLEX BELOW
{0x1E4C, 0x1E4D}, // LATIN LETTER O WITH TILDE AND ACUTE
{0x1E4E, 0x1E4F}, // LATIN LETTER O WITH TILDE AND DIAERESIS
{0x1E50, 0x1E51}, // LATIN LETTER O WITH MACRON AND GRAVE
{0x1E52, 0x1E53}, // LATIN LETTER O WITH MACRON AND ACUTE
{0x1E54, 0x1E55}, // LATIN LETTER P WITH ACUTE
{0x1E56, 0x1E57}, // LATIN LETTER P WITH DOT ABOVE
{0x1E58, 0x1E59}, // LATIN LETTER R WITH DOT ABOVE
{0x1E5A, 0x1E5B}, // LATIN LETTER R WITH DOT BELOW
{0x1E5C, 0x1E5D}, // LATIN LETTER R WITH DOT BELOW AND MACRON
{0x1E5E, 0x1E5F}, // LATIN LETTER R WITH LINE BELOW
{0x1E60, 0x1E61}, // LATIN LETTER S WITH DOT ABOVE
{0x1E62, 0x1E63}, // LATIN LETTER S WITH DOT BELOW
{0x1E64, 0x1E65}, // LATIN LETTER S WITH ACUTE AND DOT ABOVE
{0x1E66, 0x1E67}, // LATIN LETTER S WITH CARON AND DOT ABOVE
{0x1E68, 0x1E69}, // LATIN LETTER S WITH DOT BELOW AND DOT ABOVE
{0x1E6A, 0x1E6B}, // LATIN LETTER T WITH DOT ABOVE
{0x1E6C, 0x1E6D}, // LATIN LETTER T WITH DOT BELOW
{0x1E6E, 0x1E6F}, // LATIN LETTER T WITH LINE BELOW
{0x1E70, 0x1E71}, // LATIN LETTER T WITH CIRCUMFLEX BELOW
{0x1E72, 0x1E73}, // LATIN LETTER U WITH DIAERESIS BELOW
{0x1E74, 0x1E75}, // LATIN LETTER U WITH TILDE BELOW
{0x1E76, 0x1E77}, // LATIN LETTER U WITH CIRCUMFLEX BELOW
{0x1E78, 0x1E79}, // LATIN LETTER U WITH TILDE AND ACUTE
{0x1E7A, 0x1E7B}, // LATIN LETTER U WITH MACRON AND DIAERESIS
{0x1E7C, 0x1E7D}, // LATIN LETTER V WITH TILDE
{0x1E7E, 0x1E7F}, // LATIN LETTER V WITH DOT BELOW
{0x1E80, 0x1E81}, // LATIN LETTER W WITH GRAVE
{0x1E82, 0x1E83}, // LATIN LETTER W WITH ACUTE
{0x1E84, 0x1E85}, // LATIN LETTER W WITH DIAERESIS
{0x1E86, 0x1E87}, // LATIN LETTER W WITH DOT ABOVE
{0x1E88, 0x1E89}, // LATIN LETTER W WITH DOT BELOW
{0x1E8A, 0x1E8B}, // LATIN LETTER X WITH DOT ABOVE
{0x1E8C, 0x1E8D}, // LATIN LETTER X5 WITH DIAERESIS
{0x1E8E, 0x1E8F}, // LATIN LETTER Y WITH DOT ABOVE
{0x1E90, 0x1E91}, // LATIN LETTER Z WITH CIRCUMFLEX
{0x1E92, 0x1E93}, // LATIN LETTER Z WITH DOT BELOW
{0x1E94, 0x1E95}, // LATIN LETTER Z WITH LINE BELOW
{0x1EA0, 0x1EA1}, // LATIN LETTER A WITH DOT BELOW
{0x1EA2, 0x1EA3}, // LATIN LETTER A WITH HOOK ABOVE
{0x1EA4, 0x1EA5}, // LATIN LETTER A WITH CIRCUMFLEX AND ACUTE
{0x1EA6, 0x1EA7}, // LATIN LETTER A WITH CIRCUMFLEX AND GRAVE
{0x1EA8, 0x1EA9}, // LATIN LETTER A WITH CIRCUMFLEX AND HOOK ABOVE
{0x1EAA, 0x1EAB}, // LATIN LETTER A WITH CIRCUMFLEX AND TILDE
{0x1EAC, 0x1EAD}, // LATIN LETTER A WITH CIRCUMFLEX AND DOT BELOW
{0x1EAE, 0x1EAF}, // LATIN LETTER A WITH BREVE AND ACUTE
{0x1EB0, 0x1EB1}, // LATIN LETTER A WITH BREVE AND GRAVE
{0x1EB2, 0x1EB3}, // LATIN LETTER A WITH BREVE AND HOOK ABOVE
{0x1EB4, 0x1EB5}, // LATIN LETTER A WITH BREVE AND TILDE
{0x1EB6, 0x1EB7}, // LATIN LETTER A WITH BREVE AND DOT BELOW
{0x1EB8, 0x1EB9}, // LATIN LETTER E WITH DOT BELOW
{0x1EBA, 0x1EBB}, // LATIN LETTER E WITH HOOK ABOVE
{0x1EBC, 0x1EBD}, // LATIN LETTER E WITH TILDE
{0x1EBE, 0x1EBF}, // LATIN LETTER E WITH CIRCUMFLEX AND ACUTE
{0x1EC0, 0x1EC1}, // LATIN LETTER E WITH CIRCUMFLEX AND GRAVE
{0x1EC2, 0x1EC3}, // LATIN LETTER E WITH CIRCUMFLEX AND HOOK ABOVE
{0x1EC4, 0x1EC5}, // LATIN LETTER E WITH CIRCUMFLEX AND TILDE
{0x1EC6, 0x1EC7}, // LATIN LETTER E WITH CIRCUMFLEX AND DOT BELOW
{0x1EC8, 0x1EC9}, // LATIN LETTER I WITH HOOK ABOVE
{0x1ECA, 0x1ECB}, // LATIN LETTER I WITH DOT BELOW
{0x1ECC, 0x1ECD}, // LATIN LETTER O WITH DOT BELOW
{0x1ECE, 0x1ECF}, // LATIN LETTER O WITH HOOK ABOVE
{0x1ED0, 0x1ED1}, // LATIN LETTER O WITH CIRCUMFLEX AND ACUTE
{0x1ED2, 0x1ED3}, // LATIN LETTER O WITH CIRCUMFLEX AND GRAVE
{0x1ED4, 0x1ED5}, // LATIN LETTER O WITH CIRCUMFLEX AND HOOK ABOVE
{0x1ED6, 0x1ED7}, // LATIN LETTER O WITH CIRCUMFLEX AND TILDE
{0x1ED8, 0x1ED9}, // LATIN LETTER O WITH CIRCUMFLEX AND DOT BELOW
{0x1EDA, 0x1EDB}, // LATIN LETTER O WITH HORN AND ACUTE
{0x1EDC, 0x1EDD}, // LATIN LETTER O WITH HORN AND GRAVE
{0x1EDE, 0x1EDF}, // LATIN LETTER O WITH HORN AND HOOK ABOVE
{0x1EE0, 0x1EE1}, // LATIN LETTER O WITH HORN AND TILDE
{0x1EE2, 0x1EE3}, // LATIN LETTER O WITH HORN AND DOT BELOW
{0x1EE4, 0x1EE5}, // LATIN LETTER U WITH DOT BELOW
{0x1EE6, 0x1EE7}, // LATIN LETTER U WITH HOOK ABOVE
{0x1EE8, 0x1EE9}, // LATIN LETTER U WITH HORN AND ACUTE
{0x1EEA, 0x1EEB}, // LATIN LETTER U WITH HORN AND GRAVE
{0x1EEC, 0x1EED}, // LATIN LETTER U WITH HORN AND HOOK ABOVE
{0x1EEE, 0x1EEF}, // LATIN LETTER U WITH HORN AND TILDE
{0x1EF0, 0x1EF1}, // LATIN LETTER U WITH HORN AND DOT BELOW
{0x1EF2, 0x1EF3}, // LATIN LETTER Y WITH GRAVE
{0x1EF4, 0x1EF5}, // LATIN LETTER Y WITH DOT BELOW
{0x1EF6, 0x1EF7}, // LATIN LETTER Y WITH HOOK ABOVE
{0x1EF8, 0x1EF9}, // LATIN LETTER Y WITH TILDE
{0x1F08, 0x1F00}, // GREEK LETTER ALPHA WITH PSILI
{0x1F09, 0x1F01}, // GREEK LETTER ALPHA WITH DASIA
{0x1F0A, 0x1F02}, // GREEK LETTER ALPHA WITH PSILI AND VARIA
{0x1F0B, 0x1F03}, // GREEK LETTER ALPHA WITH DASIA AND VARIA
{0x1F0C, 0x1F04}, // GREEK LETTER ALPHA WITH PSILI AND OXIA
{0x1F0D, 0x1F05}, // GREEK LETTER ALPHA WITH DASIA AND OXIA
{0x1F0E, 0x1F06}, // GREEK LETTER ALPHA WITH PSILI AND PERISPOMENI
{0x1F0F, 0x1F07}, // GREEK LETTER ALPHA WITH DASIA AND PERISPOMENI
{0x1F18, 0x1F10}, // GREEK LETTER EPSILON WITH PSILI
{0x1F19, 0x1F11}, // GREEK LETTER EPSILON WITH DASIA
{0x1F1A, 0x1F12}, // GREEK LETTER EPSILON WITH PSILI AND VARIA
{0x1F1B, 0x1F13}, // GREEK LETTER EPSILON WITH DASIA AND VARIA
{0x1F1C, 0x1F14}, // GREEK LETTER EPSILON WITH PSILI AND OXIA
{0x1F1D, 0x1F15}, // GREEK LETTER EPSILON WITH DASIA AND OXIA
{0x1F28, 0x1F20}, // GREEK LETTER ETA WITH PSILI
{0x1F29, 0x1F21}, // GREEK LETTER ETA WITH DASIA
{0x1F2A, 0x1F22}, // GREEK LETTER ETA WITH PSILI AND VARIA
{0x1F2B, 0x1F23}, // GREEK LETTER ETA WITH DASIA AND VARIA
{0x1F2C, 0x1F24}, // GREEK LETTER ETA WITH PSILI AND OXIA
{0x1F2D, 0x1F25}, // GREEK LETTER ETA WITH DASIA AND OXIA
{0x1F2E, 0x1F26}, // GREEK LETTER ETA WITH PSILI AND PERISPOMENI
{0x1F2F, 0x1F27}, // GREEK LETTER ETA WITH DASIA AND PERISPOMENI
{0x1F38, 0x1F30}, // GREEK LETTER IOTA WITH PSILI
{0x1F39, 0x1F31}, // GREEK LETTER IOTA WITH DASIA
{0x1F3A, 0x1F32}, // GREEK LETTER IOTA WITH PSILI AND VARIA
{0x1F3B, 0x1F33}, // GREEK LETTER IOTA WITH DASIA AND VARIA
{0x1F3C, 0x1F34}, // GREEK LETTER IOTA WITH PSILI AND OXIA
{0x1F3D, 0x1F35}, // GREEK LETTER IOTA WITH DASIA AND OXIA
{0x1F3E, 0x1F36}, // GREEK LETTER IOTA WITH PSILI AND PERISPOMENI
{0x1F3F, 0x1F37}, // GREEK LETTER IOTA WITH DASIA AND PERISPOMENI
{0x1F48, 0x1F40}, // GREEK LETTER OMICRON WITH PSILI
{0x1F49, 0x1F41}, // GREEK LETTER OMICRON WITH DASIA
{0x1F4A, 0x1F42}, // GREEK LETTER OMICRON WITH PSILI AND VARIA
{0x1F4B, 0x1F43}, // GREEK LETTER OMICRON WITH DASIA AND VARIA
{0x1F4C, 0x1F44}, // GREEK LETTER OMICRON WITH PSILI AND OXIA
{0x1F4D, 0x1F45}, // GREEK LETTER OMICRON WITH DASIA AND OXIA
{0x1F59, 0x1F51}, // GREEK LETTER UPSILON WITH OASIS
{0x1F5B, 0x1F53}, // GREEK LETTER UPSILON WITH DASIA AND VARIA
{0x1F5D, 0x1F55}, // GREEK LETTER UPSILON WITH DASIA AND OXIA
{0x1F5F, 0x1F57}, // GREEK LETTER UPSILON WITH DASIA AND PERISPOMENI
{0x1F68, 0x1F60}, // GREEK LETTER OMEGA WITH PSILI
{0x1F69, 0x1F61}, // GREEK LETTER OMEGA WITH DASIA
{0x1F6A, 0x1F62}, // GREEK LETTER OMEGA WITH PSILI AND VARIA
{0x1F6B, 0x1F63}, // GREEK LETTER OMEGA WITH DASIA AND VARIA
{0x1F6C, 0x1F64}, // GREEK LETTER OMEGA WITH PSILI AND OXIA
{0x1F6D, 0x1F65}, // GREEK LETTER OMEGA WITH DASIA AND OXIA
{0x1F6E, 0x1F66}, // GREEK LETTER OMEGA WITH PSILI AND PERISPOMENI
{0x1F6F, 0x1F67}, // GREEK LETTER OMEGA WITH DASIA AND PERISPOMENI
{0x1F88, 0x1F80}, // GREEK LETTER ALPHA WITh PSILI AND PROSGEGRAMMENI
{0x1F89, 0x1F81}, // GREEK LETTER ALPHA WITH DASIA AND PROSGEGRAMMENI
{0x1F8A, 0x1F82}, // GREEK LETTER ALPHA WITH PSILI AND VARIA AND PROSGEGRAMMENI
{0x1F8B, 0x1F83}, // GREEK LETTER ALPHA WITH DASIA AND VARIA AND PROSGEGRAMMENI
{0x1F8C, 0x1F84}, // GREEK LETTER ALPHA WITH PSILI AND OXIA AND PROSGEGRAMMEN
{0x1F8D, 0x1F85}, // GREEK LETTER ALPHA WITH DASIA AND OXIA AND PROSGEGRAMMEN
{0x1F8E, 0x1F86}, // GREEK LETTER ALPHA WITH PSILI AND PERISPOMENI AND PROSGEGRAMMENI
{0x1F8F, 0x1F87}, // GREEK LETTER ALPHA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI
{0x1F98, 0x1F90}, // GREEK LETTER ETA WITH PSILI AND PROSGEGRAMMENI
{0x1F99, 0x1F91}, // GREEK LETTER ETA WITH DASIA AND PROSGEGRAMMENI
{0x1F9A, 0x1F92}, // GREEK LETTER ETA WITH PSILI AND VARIA AND PROSGEGRAMMENI
{0x1F9B, 0x1F93}, // GREEK LETTER ETA WITH DASIA AND VARIA AND PROSGEGRAMMENI
{0x1F9C, 0x1F94}, // GREEK LETTER ETA WITH PSILI AND OXIA AND PROSGEGRAMMENI
{0x1F9D, 0x1F95}, // GREEK LETTER ETA WITH DASIA AND OXIA AND PROSGEGRAMMENI
{0x1F9E, 0x1F96}, // GREEK LETTER ETA WITH PSILI AND PERISPOMENI AND PROSGEGRAMMENI
{0x1F9F, 0x1F97}, // GREEK LETTER ETA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI
{0x1FA8, 0x1FA0}, // GREEK LETTER OMEGA WITH PSILI AND PROSGEGRAMMENI
{0x1FA9, 0x1FA1}, // GREEK LETTER OMEGA WITH DASIA AND PROSGEGRAMMENI
{0x1FAA, 0x1FA2}, // GREEK LETTER OMEGA WITH PSILI AND VARIA AND PROSGEGRAMMENI
{0x1FAB, 0x1FA3}, // GREEK LETTER OMEGA WITH DASIA AND VARIA AND PROSGEGRAMMENI
{0x1FAC, 0x1FA4}, // GREEK LETTER OMEGA WITH PSILI AND OXIA AND PROSGEGRAMMENI
{0x1FAD, 0x1FA5}, // GREEK LETTER OMEGA WITH DASIA AND OXIA AND PROSGEGRAMMENI
{0x1FAE, 0x1FA6}, // GREEK LETTER OMEGA WITH PSILI AND PERISPOMENI AND PROSGEGRAMMENI
{0x1FAF, 0x1FA7}, // GREEK LETTER OMECA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI
{0x1FB8, 0x1FB0}, // GREEK LETTER ALPHA WITH VRACHY
{0x1FB9, 0x1FB1}, // GREEK LETTER ALPHA WITH MACRON
{0x1FD8, 0x1FD0}, // GREEK LETTER IOTA WITH VRACHY
{0x1FD9, 0x1FD1}, // GREEK LETTER IOTA WITH MACRON
{0x1FE8, 0x1FE0}, // GREEK LETTER UPSILON WITH VRACHY
{0x1FE9, 0x1FE1}, // GREEK LETTER UPSILON WITH MACRON
{0x24B6, 0x24D0}, // CIRCLED LATIN LETTER A
{0x24B7, 0x24D1}, // CIRCLED LATIN LETTER B
{0x24B8, 0x24D2}, // CIRCLED LATIN LETTER C
{0x24B9, 0x24D3}, // CIRCLED LATIN LETTER D
{0x24BA, 0x24D4}, // CIRCLED LATIN LETTER E
{0x24BB, 0x24D5}, // CIRCLED LATIN LETTER F
{0x24BC, 0x24D6}, // CIRCLED LATIN LETTER G
{0x24BD, 0x24D7}, // CIRCLED LATIN LETTER H
{0x24BE, 0x24D8}, // CIRCLED LATIN LETTER I
{0x24BF, 0x24D9}, // CIRCLED LATIN LETTER J
{0x24C0, 0x24DA}, // CIRCLED LATIN LETTER K
{0x24C1, 0x24DB}, // CIRCLED LATIN LETTER L
{0x24C2, 0x24DC}, // CIRCLED LATIN LETTER M
{0x24C3, 0x24DD}, // CIRCLED LATIN LETTER N
{0x24C4, 0x24DE}, // CIRCLED LATIN LETTER O
{0x24C5, 0x24DF}, // CIRCLED LATIN LETTER P
{0x24C6, 0x24E0}, // CIRCLED LATIN LETTER Q
{0x24C7, 0x24E1}, // CIRCLED LATIN LETTER R
{0x24C8, 0x24E2}, // CIRCLED LATIN LETTER S
{0x24C9, 0x24E3}, // CIRCLED LATIN LETTER T
{0x24CA, 0x24E4}, // CIRCLED LATIN LETTER U
{0x24CB, 0x24E5}, // CIRCLED LATIN LETTER V
{0x24CC, 0x24E6}, // CIRCLED LATIN LETTER W
{0x24CD, 0x24E7}, // CIRCLED LATIN LETTER X
{0x24CE, 0x24E8}, // CIRCLED LATIN LETTER Y
{0x24CF, 0x24E9}, // CIRCLED LATIN LETTER Z
{0xFF21, 0xFF41}, // FULLWIDTH LATIN LETTER A
{0xFF22, 0xFF42}, // FULLWIDTH LATIN LETTER B
{0xFF23, 0xFF43}, // FULLWIDTH LATIN LETTER C
{0xFF24, 0xFF44}, // FULLWIDTH LATIN LETTER D
{0xFF25, 0xFF45}, // FULLWIDTH LATIN LETTER E
{0xFF26, 0xFF46}, // FULLWIDTH LATIN LETTER F
{0xFF27, 0xFF47}, // FULLWIDTH LATIN LETTER G
{0xFF28, 0xFF48}, // FULLWIDTH LATIN LETTER H
{0xFF29, 0xFF49}, // FULLWIDTH LATIN LETTER I
{0xFF2A, 0xFF4A}, // FULLWIDTH LATIN LETTER J
{0xFF2B, 0xFF4B}, // FULLWIDTH LATIN LETTER K
{0xFF2C, 0xFF4C}, // FULLWIDTH LATIN LETTER L
{0xFF2D, 0xFF4D}, // FULLWIDTH LATIN LETTER M
{0xFF2E, 0xFF4E}, // FULLWIDTH LATIN LETTER N
{0xFF2F, 0xFF4F}, // FULLWIDTH LATIN LETTER O
{0xFF30, 0xFF50}, // FULLWIDTH LATIN LETTER P
{0xFF31, 0xFF51}, // FULLWIDTH LATIN LETTER Q
{0xFF32, 0xFF52}, // FULLWIDTH LATIN LETTER R
{0xFF33, 0xFF53}, // FULLWIDTH LATIN LETTER S
{0xFF34, 0xFF54}, // FULLWIDTH LATIN LETTER T
{0xFF35, 0xFF55}, // FULLWIDTH LATIN LETTER U
{0xFF36, 0xFF56}, // FULLWIDTH LATIN LETTER V
{0xFF37, 0xFF57}, // FULLWIDTH LATIN LETTER W
{0xFF38, 0xFF58}, // FULLWIDTH LATIN LETTER X
{0xFF39, 0xFF59}, // FULLWIDTH LATIN LETTER Y
{0xFF3A, 0xFF5A}, // FULLWIDTH LATIN LETTER Z
