/**
 * 将JSON对象转换为URL编码的字符串
 * @param {Object} json - 要转换的JSON对象
 * @returns {string} URL编码的字符串
 */
export default function jsonToUrlEncoded(json: Record<string, string>) {
  const params = new URLSearchParams();
  for (const key in json) {
    if (json.hasOwnProperty(key)) {
      params.append(key, json[key] ?? '');
    }
  }
  return params.toString();
}