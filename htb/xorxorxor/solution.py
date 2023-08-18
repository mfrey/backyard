#/usr/bin/env python3

# solution for the xorxorxor challenge on htb

# the largest two byte number (255) in hex
upper_limit = 0xFF

def _get_key(encoded: bytes, decoded: bytes) -> bytes:
   for potential_key in range(upper_limit):
      if (int(encoded, 16) ^ potential_key == ord(decoded)):
         return potential_key

def _get_flag_characters(file_name: str) -> list[bytes]:
   result = []
   # read the file two byte-wise
   with open(file_name, 'rb') as f:
      while (bytes := f.read(2)):
         result.append(bytes)

   return result

def _decode(flag: list[bytes], key: list[bytes]) -> bytes:
   result = b""
   # convert the flag
   flag = [int(e, 16) for e in flag]
   
   for i in range(len(flag)):
      result += bytes([flag[i] ^ key[i % 4]])
   return result

def main() -> None:
   # removed the 'Flag: ' bit from the file 'output.txt' and put it
   # in a file 'modified.txt'
   encoded_flag = _get_flag_characters('modified.txt')
   key = []
   # we know that the flag begins with 'HTB{', and hence
   # already know the first four decoded characters.
   clear_text = encoded_flag[0:4]
   for idx, character in enumerate(['H', 'T', 'B', '{']):
      key.append(_get_key(clear_text[idx], character))

   print(f'the key is: {key}')
   # last byte is a newline, so we only consider the encoded_flag
   # until the newline (hence, the slicing of the array)
   decoded_flag = _decode(encoded_flag[0:-1], key)
   print(f'the decoded flag is: {decoded_flag}')

if __name__ == "__main__":
   main()
