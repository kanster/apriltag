#ifndef APRILTAGS_TAGFAMILY_H_
#define APRILTAGS_TAGFAMILY_H_

#include <climits>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <map>

#include "AprilTags/TagCodes.h"
#include "AprilTags/TagDetection.h"

namespace AprilTags {

//! Generic class for all tag encoding families
class TagFamily {
 public:
  explicit TagFamily(const TagCodes& tag_codes);

  unsigned payload_bits() const;
  unsigned dimension_bits() const;
  unsigned min_hamming() const;
  const std::vector<code_t>& codes() const;
  size_t num_codes() const;

  void set_error_recovery_bits(unsigned error_recovery_bits);
  void set_error_recovery_fraction(float v);

  code_t Code(unsigned id) const;

  /**
   * @brief decode Recover id from observed code
   * @param det
   * @param obs_code
   */
  TagDetection Decode(code_t obs_code) const;

  bool IsGood(unsigned id, unsigned hamming_distance) const;

 private:
  const TagCodes& tag_codes_;
  const size_t num_codes_;

  /**
   * @brief error_recovery_bits_
   * The error recovery value determines our position on the ROC curve. We will
   * report codes that are within error_recovery_bits_ of a valid code. Small
   * values mean greater rejection of bogus tags (but false negatives). Large
   * values mean aggressive reporting of bad tags (but with a corresponind
   * increase in false positives).
   */
  unsigned error_recovery_bits_;
};

/* if the bits in w were arranged in a d*d grid and that grid was
 * rotated, what would the new bits in w be?
 * The bits are organized like this (for d = 3):
 *
 *  8 7 6       2 5 8      0 1 2
 *  5 4 3  ==>  1 4 7 ==>  3 4 5    (rotate90 applied twice)
 *  2 1 0       0 3 6      6 7 8
 */
code_t Rotate90Cwise(code_t w, int d);

unsigned HammingDistance(code_t a, code_t b);

unsigned PopCount(code_t w);

}  // namespace AprilTags

#endif  // APRILTAGS_TAGFAMILY_H_
