#include <assert.h>
#include <string.h>
#include "binson_parser.h"

/*
{
  "A": "B", 
  "B": 1, 
  "C": 3.0000038146972656, 
  "D": false, 
  "E": "0x0100", 
  "F": {
  }, 
  "G": [
    "0x01140143460000000002000840140144",
    false,
    " ",
    "F",
    {
    },
    "G",
    [
      "0x0102",
      "",
      "E",
      false,
      false,
      "A",
      "B",
      "B",
      1,
      "C",
      3.0000038146972656,
      "D",
      false,
      "E",
      "0x0100",
      "F",
      {
      },
      "G",
      [
        "0x0102",
        "",
        "E",
        false,
        false,
        false,
        "?E",
        false,
        false,
        false,
        false,
        false,
        false,
        {
          "A": "B", 
          "B": 1, 
          "C": 3.0000038146972656, 
          "D": false, 
          "E": "0x0100", 
          "F": {
          }, 
          "G": [
            false,
            "A",
            "0x0102",
            "EEEE",
            "?EEE",
            false,
            false,
            false,
            false,
            {
              "E": "E"
            },
            "C",
            2.1747253248E10,
            1,
            "C",
            9.665790144E9
          ], 
          "?": [
            
          ]
        },
        {
          "E": "E"
        },
        "B",
        "B",
        1,
        "C",
        2.1747253248E10,
        1,
        "C",
        "EEEE",
        "?EEEE",
        false,
        false,
        false,
        {
          "A": "B", 
          "B": 1, 
          "C": 3.0000038146972656, 
          "D": false, 
          "E": "0x0100", 
          "G": [
            false,
            "A",
            "0x0102",
            "E",
            false,
            false,
            false,
            "?E",
            false,
            false,
            false,
            false,
            false,
            false,
            {
              "E": "E"
            },
            "C",
            2.1747253248E10,
            1,
            "C",
            9.665790144E9
          ], 
          "?": [
            
          ]
        },
        {
          "E": "E"
        },
        "B",
        9.665790144E9
      ],
      "?",
      false,
      "?E",
      false,
      false,
      false,
      false,
      false,
      false,
      {
        "A": "B", 
        "B": 1, 
        "C": 3.0000038146972656, 
        "D": false, 
        "E": "0x0100", 
        "F": {
        }, 
        "G": [
          false,
          "A",
          "0x0102",
          "EEEE",
          "?EEE",
          false,
          false,
          false,
          false,
          {
            "E": "E"
          },
          "C",
          2.1747253248E10,
          1,
          "C",
          9.665790144E9
        ], 
        "?": [
          
        ]
      },
      {
        "E": "E"
      },
      "B",
      "B",
      1,
      "C",
      2.1747253248E10,
      1,
      "C",
      "EEEE",
      "?EEEE",
      false,
      false,
      false,
      {
        "A": "B", 
        "B": 1, 
        "C": 3.0000038146972656, 
        "D": false, 
        "E": "0x0100", 
        "F": {
        }, 
        "G": [
          false,
          "A",
          "0x0102",
          "EEEE",
          "?EEE",
          false,
          false,
          false,
          false,
          {
            "E": "E"
          },
          "C",
          2.1747253248E10,
          1,
          "C",
          9.665790144E9
        ], 
        "?": [
          
        ]
      },
      {
        "E": "E"
      },
      "B",
      9.665790144E9
    ],
    "",
    "",
    "E",
    false,
    false,
    "A",
    "B",
    "B",
    1,
    "C",
    3.0000038146972656,
    "D",
    false,
    "E",
    "0x0100",
    "F",
    {
    },
    "G",
    [
      "0x0102",
      "",
      "E",
      false,
      false,
      false,
      "?E",
      false,
      false,
      false,
      false,
      false,
      false,
      {
        "A": "B", 
        "B": 1, 
        "C": 3.0000038146972656, 
        "D": false, 
        "E": "0x0100", 
        "F": {
        }, 
        "G": [
          false,
          "A",
          "0x0102",
          "EEEE",
          "?EEE",
          false,
          false,
          false,
          false,
          {
            "E": "E"
          },
          "C",
          2.1747253248E10,
          1,
          "C",
          9.665790144E9
        ], 
        "?": [
          
        ]
      },
      {
        "E": "E"
      },
      "B",
      "B",
      1,
      "C",
      2.1747253248E10,
      1,
      "C",
      "EEEE",
      "?EEEE",
      false,
      false,
      false,
      {
        "A": "B", 
        "B": 1, 
        "C": 3.0000038146972656, 
        "D": false, 
        "E": "0x0100", 
        "G": [
          false,
          "A",
          "0x0102",
          "E",
          false,
          false,
          false,
          "?E",
          false,
          false,
          false,
          false,
          false,
          false,
          {
            "E": "E"
          },
          "C",
          2.1747253248E10,
          1,
          "C",
          9.665790144E9
        ], 
        "?": [
          
        ]
      },
      {
        "E": "E"
      },
      "B",
      9.665790144E9
    ],
    "?",
    false,
    "?E",
    false,
    false,
    false,
    false,
    false,
    false,
    {
      "A": "B", 
      "B": 1, 
      "C": 3.0000038146972656, 
      "D": false, 
      "E": "0x0100", 
      "F": {
      }, 
      "G": [
        false,
        "A",
        "0x0102",
        "EEEE",
        "?EEE",
        false,
        false,
        false,
        false,
        {
          "E": "E"
        },
        "C",
        2.1747253248E10,
        1,
        "C",
        9.665790144E9
      ], 
      "?": [
        
      ]
    },
    {
      "E": "E"
    },
    "B",
    "B",
    1,
    "C",
    2.1747253248E10,
    1,
    "C",
    "EEEE",
    "?EEEE",
    false,
    false,
    false,
    {
      "A": "B", 
      "B": 1, 
      "C": 3.0000038146972656, 
      "D": false, 
      "E": "0x0100", 
      "F": {
      }, 
      "G": [
        false,
        "A",
        "0x0102",
        "EEEE",
        "?EEE",
        false,
        false,
        false,
        false,
        {
          "E": "E"
        },
        "C",
        2.1747253248E10,
        1,
        "C",
        9.665790144E9
      ], 
      "?": [
        
      ]
    },
    {
      "E": "E"
    },
    "B",
    9.665790144E9
  ], 
  "?": [
    
  ]
}
*/
int main(void)
{
    uint8_t binson_bytes[1999] = "\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x00\x02\x00\x08\x40\x14\x01\x44\x45\x14\x01\x45\x18\x02\x01\x00\x14\x01\x46\x40\x41\x14\x01\x47\x42\x18\x10\x01\x14\x01\x43\x46\x00\x00\x00\x00\x02\x00\x08\x40\x14\x01\x44\x45\x14\x01\x00\x14\x01\x46\x40\x41\x14\x01\x47\x42\x18\x02\x01\x02\x14\x01\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x1e\x14\x14\x14\x14\x14\x45\x45\x45\x14\x01\x41\x14\x01\x42\x14\x01\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x00\x02\x00\x08\x40\x14\x01\x44\x45\x14\x01\x45\x18\x02\x01\x00\x14\x01\x46\x40\x41\x14\x01\x47\x42\x18\x02\x01\x02\x14\x01\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x1e\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x16\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45\x45\x45\x45\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x00\x02\x00\x08\x40\x14\x01\x44\x45\x14\x01\x45\x18\x02\x01\x00\x14\x01\x46\x40\x41\x14\x01\x47\x42\x45\x14\x01\x41\x18\x02\x01\x02\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14\x14\x16\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45\x45\x45\x45\x40\x14\x01\x45\x14\x01\x45\x41\x14\x01\x43\x46\x00\x00\x00\x00\xf3\x40\x14\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x06\x02\x01\x02\x42\x43\x14\x03\xef\xbf\xbd\x42\x43\x41\x40\x14\x01\x45\x14\x01\x45\x41\x14\x01\x42\x14\x01\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x00\xf3\x40\x14\x42\x10\x01\x14\x01\x43\x14\x14\x14\x14\x14\x14\x14\x14\x14\x1e\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14\x14\x14\x16\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x10\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45\x45\x45\x45\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x00\x02\x00\x08\x40\x14\x01\x44\x45\x14\x01\x45\x18\x02\x01\x00\x14\x01\x47\x42\x45\x14\x01\x41\x18\x02\x01\x02\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x16\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45\x45\x45\x45\x40\x14\x01\x45\x14\x01\x45\x41\x14\x01\x43\x46\x00\x00\x00\x00\xf3\x40\x14\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x06\x02\x01\x02\x42\x43\x14\x03\xef\xbf\xbd\x42\x43\x41\x40\x14\x01\x45\x14\x01\x45\x41\x14\x01\x42\x46\x00\x00\x00\x06\x02\x01\x02\x42\x43\x14\x03\xef\xbf\xbd\x45\x14\x16\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45\x45\x45\x45\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x00\x02\x00\x08\x40\x14\x01\x44\x45\x14\x01\x45\x18\x02\x01\x00\x14\x01\x46\x40\x41\x14\x01\x47\x42\x45\x14\x01\x41\x18\x02\x01\x02\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14\x14\x16\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45\x45\x45\x45\x40\x14\x01\x45\x14\x01\x45\x41\x14\x01\x43\x46\x00\x00\x00\x00\xf3\x40\x14\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x06\x02\x01\x02\x42\x43\x14\x03\xef\xbf\xbd\x42\x43\x41\x40\x14\x01\x45\x14\x01\x45\x41\x14\x01\x42\x14\x01\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x00\xf3\x40\x14\x42\x10\x01\x14\x01\x43\x14\x14\x14\x14\x14\x14\x14\x14\x14\x1e\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14\x14\x14\x16\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45\x45\x45\x45\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x00\x02\x00\x08\x40\x14\x01\x44\x45\x14\x01\x45\x18\x02\x01\x00\x14\x01\x46\x40\x41\x14\x01\x47\x42\x45\x14\x01\x41\x18\x02\x01\x02\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14\x14\x16\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45\x45\x45\x45\x40\x14\x01\x45\x14\x01\x45\x41\x14\x01\x43\x46\x00\x00\x00\x00\xf3\x40\x14\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x06\x02\x01\x02\x42\x43\x14\x03\xef\xbf\xbd\x42\x43\x41\x40\x14\x01\x45\x14\x01\x45\x41\x14\x01\x42\x46\x00\x00\x00\x06\x02\x01\x02\x42\x43\x14\x02\x01\x02\x14\x01\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x1e\x14\x14\x14\x14\x14\x45\x45\x45\x14\x01\x41\x14\x01\x42\x14\x01\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x00\x02\x00\x08\x40\x14\x01\x44\x45\x14\x01\x45\x18\x02\x01\x00\x14\x01\x46\x40\x41\x14\x01\x47\x42\x18\x02\x01\x02\x14\x01\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x1e\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x16\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45\x45\x45\x45\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x00\x02\x00\x08\x40\x14\x01\x44\x45\x14\x01\x45\x18\x02\x01\x00\x14\x01\x46\x40\x41\x14\x01\x47\x42\x45\x14\x01\x41\x18\x02\x01\x02\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14\x14\x16\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45\x45\x45\x45\x40\x14\x01\x45\x14\x01\x45\x41\x14\x01\x43\x46\x00\x00\x00\x00\xf3\x40\x14\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x06\x02\x01\x02\x42\x43\x14\x03\xef\xbf\xbd\x42\x43\x41\x40\x14\x01\x45\x14\x01\x45\x41\x14\x01\x42\x14\x01\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x00\xf3\x40\x14\x42\x10\x01\x14\x01\x43\x14\x14\x14\x14\x14\x14\x14\x14\x14\x1e\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14\x14\x14\x16\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x10\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45\x45\x45\x45\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x00\x02\x00\x08\x40\x14\x01\x44\x45\x14\x01\x45\x18\x02\x01\x00\x14\x01\x47\x42\x45\x14\x01\x41\x18\x02\x01\x02\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x16\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45\x45\x45\x45\x40\x14\x01\x45\x14\x01\x45\x41\x14\x01\x43\x46\x00\x00\x00\x00\xf3\x40\x14\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x06\x02\x01\x02\x42\x43\x14\x03\xef\xbf\xbd\x42\x43\x41\x40\x14\x01\x45\x14\x01\x45\x41\x14\x01\x42\x46\x00\x00\x00\x06\x02\x01\x02\x42\x43\x14\x03\xef\xbf\xbd\x45\x14\x16\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45\x45\x45\x45\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x00\x02\x00\x08\x40\x14\x01\x44\x45\x14\x01\x45\x18\x02\x01\x00\x14\x01\x46\x40\x41\x14\x01\x47\x42\x45\x14\x01\x41\x18\x02\x01\x02\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14\x14\x16\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45\x45\x45\x45\x40\x14\x01\x45\x14\x01\x45\x41\x14\x01\x43\x46\x00\x00\x00\x00\xf3\x40\x14\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x06\x02\x01\x02\x42\x43\x14\x03\xef\xbf\xbd\x42\x43\x41\x40\x14\x01\x45\x14\x01\x45\x41\x14\x01\x42\x14\x01\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x00\xf3\x40\x14\x42\x10\x01\x14\x01\x43\x14\x14\x14\x14\x14\x14\x14\x14\x14\x1e\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14\x14\x14\x16\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45\x45\x45\x45\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x00\x02\x00\x08\x40\x14\x01\x44\x45\x14\x01\x45\x18\x02\x01\x00\x14\x01\x46\x40\x41\x14\x01\x47\x42\x45\x14\x01\x41\x18\x02\x01\x02\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14\x14\x16\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45\x45\x45\x45\x40\x14\x01\x45\x14\x01\x45\x41\x14\x01\x43\x46\x00\x00\x00\x00\xf3\x40\x14\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x06\x02\x01\x02\x42\x43\x14\x03\xef\xbf\xbd\x42\x43\x41\x40\x14\x01\x45\x14\x01\x45\x41\x14\x01\x42\x46\x00\x00\x00\x06\x02\x01\x02\x42\x43\x14\x03\xef\xbf\xbd\x42\x43\x41";
    BINSON_PARSER_DEF(p);
    double dval; (void) dval;
    int64_t intval; (void) intval;
    bool boolval; (void) boolval;
    bbuf *rawval; (void) rawval;
    assert(binson_parser_init(&p, binson_bytes, sizeof(binson_bytes)));
    assert(binson_parser_verify(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x41", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x42", 1, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_field_ensure_with_length(&p, "\x43", 1, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 3.0000038146972656);
    assert(binson_parser_field_ensure_with_length(&p, "\x44", 1, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x00", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x46", 1, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x47", 1, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x14\x01\x43\x46\x00\x00\x00\x00\x02\x00\x08\x40\x14\x01\x44", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x00", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x46", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x47", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x02", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x1e\x14\x14\x14\x14\x14\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x41", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 3.0000038146972656);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x44", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x00", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x46", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x47", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x02", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x1e\x14\x14\x14\x14\x14\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x41", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x42", 1, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_field_ensure_with_length(&p, "\x43", 1, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 3.0000038146972656);
    assert(binson_parser_field_ensure_with_length(&p, "\x44", 1, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x00", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x46", 1, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x47", 1, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x41", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x02", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 2.1747253248E10);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 9.665790144E9);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\xef\xbf\xbd", 3, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 2.1747253248E10);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x1e\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14\x14", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x10\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x41", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x42", 1, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_field_ensure_with_length(&p, "\x43", 1, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 3.0000038146972656);
    assert(binson_parser_field_ensure_with_length(&p, "\x44", 1, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x00", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x47", 1, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x41", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x02", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 2.1747253248E10);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 9.665790144E9);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\xef\xbf\xbd", 3, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 9.665790144E9);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\xef\xbf\xbd", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x41", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x42", 1, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_field_ensure_with_length(&p, "\x43", 1, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 3.0000038146972656);
    assert(binson_parser_field_ensure_with_length(&p, "\x44", 1, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x00", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x46", 1, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x47", 1, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x41", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x02", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 2.1747253248E10);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 9.665790144E9);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\xef\xbf\xbd", 3, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 2.1747253248E10);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x1e\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14\x14", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x41", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x42", 1, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_field_ensure_with_length(&p, "\x43", 1, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 3.0000038146972656);
    assert(binson_parser_field_ensure_with_length(&p, "\x44", 1, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x00", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x46", 1, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x47", 1, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x41", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x02", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 2.1747253248E10);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 9.665790144E9);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\xef\xbf\xbd", 3, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 9.665790144E9);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x02", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x1e\x14\x14\x14\x14\x14\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x41", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 3.0000038146972656);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x44", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x00", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x46", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x47", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x02", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x1e\x14\x14\x14\x14\x14\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x41", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x42", 1, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_field_ensure_with_length(&p, "\x43", 1, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 3.0000038146972656);
    assert(binson_parser_field_ensure_with_length(&p, "\x44", 1, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x00", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x46", 1, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x47", 1, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x41", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x02", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 2.1747253248E10);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 9.665790144E9);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\xef\xbf\xbd", 3, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 2.1747253248E10);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x1e\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14\x14", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x10\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x41", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x42", 1, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_field_ensure_with_length(&p, "\x43", 1, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 3.0000038146972656);
    assert(binson_parser_field_ensure_with_length(&p, "\x44", 1, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x00", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x47", 1, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x41", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x02", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 2.1747253248E10);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 9.665790144E9);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\xef\xbf\xbd", 3, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 9.665790144E9);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\xef\xbf\xbd", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x41", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x42", 1, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_field_ensure_with_length(&p, "\x43", 1, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 3.0000038146972656);
    assert(binson_parser_field_ensure_with_length(&p, "\x44", 1, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x00", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x46", 1, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x47", 1, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x41", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x02", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 2.1747253248E10);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 9.665790144E9);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\xef\xbf\xbd", 3, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 2.1747253248E10);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x1e\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14\x14", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x41", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x42", 1, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_field_ensure_with_length(&p, "\x43", 1, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 3.0000038146972656);
    assert(binson_parser_field_ensure_with_length(&p, "\x44", 1, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x00", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x46", 1, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x47", 1, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x41", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x02", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x45\x45\x45\x45\x14\x14", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x13\xef\xbf\xbd\x45\x45\x45", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 2.1747253248E10);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x43", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 9.665790144E9);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\xef\xbf\xbd", 3, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x45", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 9.665790144E9);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\xef\xbf\xbd", 3, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    return 0;
}

