/**
 * Parses a build date string provided by SDK.
 *
 * @param dateString - The date string to parse. The format is expected to be "yMMdd", where "y" is the year offset from 2017, "MM" is the month, and "dd" is the day.
 * @returns The parsed date in the format "dd/mm/yyyy".
 * @throws An error if the date string is not in the expected format.
 */
export const parseBuildDate = (dateString: string): string => {
  if (dateString.length !== 5) {
    throw new Error('Invalid date string format. Expected format is YMMDD.')
  }

  const [year, month, day] = [+dateString.charAt(0) + 2017, dateString.slice(1, 3), dateString.slice(3, 5)]

  if (Number.isNaN(year) || Number.isNaN(Number(month)) || Number.isNaN(Number(day))) {
    throw new Error('Invalid date string format. Expected format is YMMDD.')
  }

  return `${day}/${month}/${year}`
}
