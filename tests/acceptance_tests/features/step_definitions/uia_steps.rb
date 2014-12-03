When(/^(\w+) creates? asset ([A-Z]+) \(max shares: ([\d,]+)\)$/) do |name, asset, max_shares|
  actor = get_actor(name)
  max_shares.gsub!(',','')
  actor.node.exec 'wallet_asset_create', asset, asset.downcase + '_iou', actor.account, asset.downcase + '_iou_description', max_shares.to_i, 1000, '', false
end

When(/^(\w+) issues? ([\d,]+) ([A-Z]+) shares to (\w+)$/) do |name, amount, symbol, to_name|
  actor = get_actor(name)
  amount.gsub!(',','')
  to = get_actor(to_name)
  actor.node.exec 'wallet_asset_issue', amount, symbol, to.account, 'minted shares'
end

Then(/^(\w+) should see the following assets:$/) do |name, table|
  actor = get_actor(name)
  assets = table.hashes.map { |r| r }
  res = actor.node.exec 'blockchain_list_assets'
  res_hash = {}
  res.each{|a| res_hash[a['symbol']] = a}
  assets.each do |a|
    ra = res_hash[a['Symbol']]
    raise "Asset #{a['symbol']} nof found in #{JSON.pretty_generate(res)}" unless ra
    a.each do |k,v|
      expect(ra[k.downcase.gsub(' ','_')].to_s).to eq(v.to_s)
    end
  end
end
